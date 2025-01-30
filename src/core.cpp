/* SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright © 2025 The TokTok team.
 */
#include "core.h"

#include "coreoptions.h"

#include "src/models/coreevent.h"

#include <tox/tox.h>
#include <tox/tox_events.h>

void Tox_Deleter::operator()(Tox* tox) const
{
    tox_kill(tox);
}

struct Tox_Events_Deleter
{
    void operator()(Tox_Events* events) const
    {
        tox_events_free(events);
    }
};

Core::Core(CoreOptions* options, QObject* parent)
    : QObject(parent)
    , tox(tox_new(options->get(), nullptr))
{
    // Should at least work with default options.
    Q_ASSERT(tox != nullptr);
    tox_events_init(tox.get());
    connect(&iterateTimer, &QTimer::timeout, this, [this]() {
        Tox_Err_Events_Iterate err;
        std::unique_ptr<Tox_Events, Tox_Events_Deleter> events{
            tox_events_iterate(tox.get(), true, &err),
        };
        if (err != TOX_ERR_EVENTS_ITERATE_OK) {
            qWarning("Failed to iterate events: %d", err);
        }
        const size_t count = tox_events_get_size(events.get());
        for (size_t i = 0; i < count; ++i) {
            auto event = CoreEvent::fromTox(tox_events_get(events.get(), i));
            if (event) {
                emit eventReceived(QSharedPointer<CoreEvent>(event.release()));
            }
        }
    });
}

Core::~Core() = default;

void Core::start()
{
    iterateTimer.setInterval(tox_iteration_interval(tox.get()));
    iterateTimer.setSingleShot(false);
    iterateTimer.start();
}

void Core::stop()
{
    iterateTimer.stop();
}

QString Core::reload(CoreOptions* options)
{
    QByteArray savedata;
    savedata.resize(tox_get_savedata_size(tox.get()));
    tox_get_savedata(tox.get(), reinterpret_cast<uint8_t*>(savedata.data()));

    options->setSavedata(savedata);

    Tox_Err_New err;
    std::unique_ptr<Tox, Tox_Deleter> newTox(tox_new(options->get(), &err));
    if (err != TOX_ERR_NEW_OK) {
        return QStringLiteral("Failed to create new Tox instance: %1")
            .arg(QString::fromUtf8(tox_err_new_to_string(err)));
    }
    tox = std::move(newTox);
    return QStringLiteral("Tox instance reloaded");
}

QString Core::address() const
{
    QByteArray address;
    address.resize(TOX_ADDRESS_SIZE);
    tox_self_get_address(tox.get(), reinterpret_cast<uint8_t*>(address.data()));
    return QString::fromUtf8(address.toHex()).toUpper();
}

QString Core::secretKey() const
{
    QByteArray secretKey;
    secretKey.resize(TOX_SECRET_KEY_SIZE);
    tox_self_get_secret_key(tox.get(), reinterpret_cast<uint8_t*>(secretKey.data()));
    return QString::fromUtf8(secretKey.toHex()).toUpper();
}

QString Core::bootstrap(const QString& address, uint16_t port, const QByteArray& public_key)
{
    if (public_key.size() != TOX_PUBLIC_KEY_SIZE) {
        return QStringLiteral("Invalid public key size: %1 != %2").arg(public_key.size()).arg(TOX_PUBLIC_KEY_SIZE);
    }
    Tox_Err_Bootstrap err;
    tox_bootstrap(tox.get(), address.toUtf8().constData(), port,
                  reinterpret_cast<const uint8_t*>(public_key.constData()), &err);
    return QString::fromUtf8(tox_err_bootstrap_to_string(err));
}

QString Core::addTcpRelay(const QString& address, uint16_t port, const QByteArray& public_key)
{
    if (public_key.size() != TOX_PUBLIC_KEY_SIZE) {
        return QStringLiteral("Invalid public key size: %1 != %2").arg(public_key.size()).arg(TOX_PUBLIC_KEY_SIZE);
    }
    Tox_Err_Bootstrap err;
    tox_add_tcp_relay(tox.get(), address.toUtf8().constData(), port,
                      reinterpret_cast<const uint8_t*>(public_key.constData()), &err);
    return QString::fromUtf8(tox_err_bootstrap_to_string(err));
}
