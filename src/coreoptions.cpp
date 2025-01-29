/* SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright © 2025 The TokTok team.
 */
#include "coreoptions.h"

#include <QLoggingCategory>

#include <tox/tox.h>

namespace {
Q_LOGGING_CATEGORY(toxCore, "tox.core")
Q_LOGGING_CATEGORY(toxTrace, "tox.trace")

void toxLogCallback(Tox* tox, TOX_LOG_LEVEL level, const char* file, uint32_t line,
                    const char* func, const char* message, void* user_data)
{
    std::ignore = tox;
    std::ignore = user_data;
    switch (level) {
    case TOX_LOG_LEVEL_TRACE:
        QMessageLogger(file, line, func).debug(toxTrace) << message;
        break;
    case TOX_LOG_LEVEL_DEBUG:
        QMessageLogger(file, line, func).debug(toxCore) << message;
        break;
    case TOX_LOG_LEVEL_INFO:
        QMessageLogger(file, line, func).info(toxCore) << message;
        break;
    case TOX_LOG_LEVEL_WARNING:
        QMessageLogger(file, line, func).warning(toxCore) << message;
        break;
    case TOX_LOG_LEVEL_ERROR:
        QMessageLogger(file, line, func).critical(toxCore) << message;
        break;
    }
}

const uint8_t* maybeLeakingMemdup(const uint8_t* mem, size_t size)
{
#if TOX_VERSION_IS_API_COMPATIBLE(0, 2, 21)
    return mem;
#else
    uint8_t* copy = new uint8_t[size];
    if (copy != nullptr) {
        std::copy(mem, mem + size, copy);
    }
    return copy;
#endif
}

const char* maybeLeakingStrdup(const char* str)
{
    return reinterpret_cast<const char*>(
        maybeLeakingMemdup(reinterpret_cast<const uint8_t*>(str), strlen(str) + 1));
}

QString boolToString(bool value)
{
    return value ? QStringLiteral("true") : QStringLiteral("false");
}

template <typename F>
QString boolFromString(const QString& value, F func)
{
    if (value == QStringLiteral("true")) {
        return func(true);
    }
    if (value == QStringLiteral("false")) {
        return func(false);
    }
    return QStringLiteral("Invalid bool value: %1").arg(value);
}

template <typename F>
QString intFromString(const QString& value, F func)
{
    bool ok;
    const int intValue = value.toInt(&ok);
    if (!ok) {
        return QStringLiteral("Invalid int value: %1").arg(value);
    }
    return func(intValue);
}

template <typename F>
QString proxyTypeFromString(const QString& value, F func)
{
    if (value == QStringLiteral("none")) {
        return func(TOX_PROXY_TYPE_NONE);
    }
    if (value == QStringLiteral("http")) {
        return func(TOX_PROXY_TYPE_HTTP);
    }
    if (value == QStringLiteral("socks5")) {
        return func(TOX_PROXY_TYPE_SOCKS5);
    }
    return QStringLiteral("Invalid proxy type: %1").arg(value);
}

template <typename F>
QString savedataTypeFromString(const QString& value, F func)
{
    if (value == QStringLiteral("tox_save")) {
        return func(TOX_SAVEDATA_TYPE_TOX_SAVE);
    }
    if (value == QStringLiteral("secret_key")) {
        return func(TOX_SAVEDATA_TYPE_SECRET_KEY);
    }
    return QStringLiteral("Invalid savedata type: %1").arg(value);
}

template <typename F>
QString bytesFromString(const QString& value, F func)
{
    const QByteArray bytes = QByteArray::fromHex(value.toUtf8());
    return func(maybeLeakingMemdup(reinterpret_cast<const uint8_t*>(bytes.constData()), bytes.size()),
                bytes.size());
}

template <typename F>
QString stringFromString(const QString& value, F func)
{
    return func(maybeLeakingStrdup(value.toUtf8().constData()));
}
} // namespace

void Tox_Options_Deleter::operator()(Tox_Options* options) const
{
    tox_options_free(options);
}

CoreOptions::CoreOptions(QObject* parent)
    : QObject(parent)
    , options(tox_options_new(nullptr))
{
    Q_ASSERT(options != nullptr);

#if TOX_VERSION_IS_API_COMPATIBLE(0, 2, 21)
    tox_options_set_experimental_owned_data(options.get(), true);
#endif
#ifdef Q_OS_WASM
    tox_options_set_udp_enabled(options.get(), false);
#endif

    tox_options_set_log_callback(options.get(), toxLogCallback);
}

CoreOptions::~CoreOptions() = default;

const Tox_Options* CoreOptions::get() const
{
    return options.get();
}

QStringList CoreOptions::toStringList() const
{
    QStringList result{
        QStringLiteral("udp_enabled: %1").arg(boolToString(tox_options_get_udp_enabled(options.get()))),
        QStringLiteral("ipv6_enabled: %1").arg(boolToString(tox_options_get_ipv6_enabled(options.get()))),
        QStringLiteral("local_discovery_enabled: %1")
            .arg(boolToString(tox_options_get_local_discovery_enabled(options.get()))),
        QStringLiteral("dht_announcements_enabled: %1")
            .arg(boolToString(tox_options_get_dht_announcements_enabled(options.get()))),
        QStringLiteral("hole_punching_enabled: %1")
            .arg(boolToString(tox_options_get_hole_punching_enabled(options.get()))),

        QStringLiteral("proxy_type: %1")
            .arg(QString::fromUtf8(tox_proxy_type_to_string(tox_options_get_proxy_type(options.get())))),
        QStringLiteral("proxy_host: %1").arg(QString::fromUtf8(tox_options_get_proxy_host(options.get()))),
        QStringLiteral("proxy_port: %1").arg(tox_options_get_proxy_port(options.get())),

        QStringLiteral("start_port: %1").arg(tox_options_get_start_port(options.get())),
        QStringLiteral("end_port: %1").arg(tox_options_get_end_port(options.get())),
        QStringLiteral("tcp_port: %1").arg(tox_options_get_tcp_port(options.get())),

        QStringLiteral("savedata_type: %1")
            .arg(QString::fromUtf8(
                tox_savedata_type_to_string(tox_options_get_savedata_type(options.get())))),
        QStringLiteral("savedata: byte[%1]").arg(tox_options_get_savedata_length(options.get())),
    };
#if TOX_VERSION_IS_API_COMPATIBLE(0, 2, 21)
    result << QStringLiteral("experimental_owned_data: %1")
                  .arg(boolToString(tox_options_get_experimental_owned_data(options.get())));
#endif

    return result;
}

void CoreOptions::setSavedata(const QByteArray& savedata)
{
    tox_options_set_savedata_data(options.get(),
                                  reinterpret_cast<const uint8_t*>(savedata.constData()),
                                  savedata.size());
    tox_options_set_savedata_type(options.get(), TOX_SAVEDATA_TYPE_TOX_SAVE);
}

QString CoreOptions::set(const QString& name, const QString& value)
{
    if (name == QStringLiteral("udp_enabled")) {
        return boolFromString(value, [this](bool value) {
            tox_options_set_udp_enabled(options.get(), value);
            return QStringLiteral("udp_enabled: %1").arg(boolToString(value));
        });
    }
    if (name == QStringLiteral("ipv6_enabled")) {
        return boolFromString(value, [this](bool value) {
            tox_options_set_ipv6_enabled(options.get(), value);
            return QStringLiteral("ipv6_enabled: %1").arg(boolToString(value));
        });
    }
    if (name == QStringLiteral("local_discovery_enabled")) {
        return boolFromString(value, [this](bool value) {
            tox_options_set_local_discovery_enabled(options.get(), value);
            return QStringLiteral("local_discovery_enabled: %1").arg(boolToString(value));
        });
    }
    if (name == QStringLiteral("dht_announcements_enabled")) {
        return boolFromString(value, [this](bool value) {
            tox_options_set_dht_announcements_enabled(options.get(), value);
            return QStringLiteral("dht_announcements_enabled: %1").arg(boolToString(value));
        });
    }
    if (name == QStringLiteral("hole_punching_enabled")) {
        return boolFromString(value, [this](bool value) {
            tox_options_set_hole_punching_enabled(options.get(), value);
            return QStringLiteral("hole_punching_enabled: %1").arg(boolToString(value));
        });
    }
    if (name == QStringLiteral("proxy_type")) {
        return proxyTypeFromString(value, [this](Tox_Proxy_Type value) {
            tox_options_set_proxy_type(options.get(), value);
            return QStringLiteral("proxy_type: %1").arg(QString::fromUtf8(tox_proxy_type_to_string(value)));
        });
    }
    if (name == QStringLiteral("proxy_host")) {
        return stringFromString(value, [this](const char* value) {
            tox_options_set_proxy_host(options.get(), value);
            return QStringLiteral("proxy_host: %1").arg(QString::fromUtf8(value));
        });
    }
    if (name == QStringLiteral("proxy_port")) {
        return intFromString(value, [this](int value) {
            tox_options_set_proxy_port(options.get(), value);
            return QStringLiteral("proxy_port: %1").arg(value);
        });
    }
    if (name == QStringLiteral("start_port")) {
        return intFromString(value, [this](int value) {
            tox_options_set_start_port(options.get(), value);
            return QStringLiteral("start_port: %1").arg(value);
        });
    }
    if (name == QStringLiteral("end_port")) {
        return intFromString(value, [this](int value) {
            tox_options_set_end_port(options.get(), value);
            return QStringLiteral("end_port: %1").arg(value);
        });
    }
    if (name == QStringLiteral("tcp_port")) {
        return intFromString(value, [this](int value) {
            tox_options_set_tcp_port(options.get(), value);
            return QStringLiteral("tcp_port: %1").arg(value);
        });
    }
    if (name == QStringLiteral("savedata_type")) {
        return savedataTypeFromString(value, [this](Tox_Savedata_Type value) {
            tox_options_set_savedata_type(options.get(), value);
            return QStringLiteral("savedata_type: %1")
                .arg(QString::fromUtf8(tox_savedata_type_to_string(value)));
        });
    }
    if (name == QStringLiteral("savedata")) {
        return bytesFromString(value, [this](const uint8_t* data, size_t size) {
            tox_options_set_savedata_data(options.get(), data, size);
            tox_options_set_savedata_length(options.get(), size);
            return QStringLiteral("savedata: byte[%1]").arg(size);
        });
    }

    return QStringLiteral("Unknown option: %1").arg(name);
}
