/* SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright © 2025 The TokTok team.
 */
#pragma once

#include "src/models/coreevent.h"

#include <QObject>
#include <QSharedPointer>
#include <QTimer>

class CoreOptions;
struct Tox;

class Tox_Deleter
{
public:
    void operator()(Tox* tox) const;
};

class Core : public QObject
{
    Q_OBJECT

public:
    Core(CoreOptions* options, QObject* parent);
    ~Core() override;

    void start();
    void stop();

    QString reload(CoreOptions* options);

    QString address() const;
    QString secretKey() const;

    QString bootstrap(const QString& address, uint16_t port, const QByteArray& public_key);
    QString addTcpRelay(const QString& address, uint16_t port, const QByteArray& public_key);

signals:
    void eventReceived(QSharedPointer<CoreEvent> event);

private:
    std::unique_ptr<Tox, Tox_Deleter> tox;
    QTimer iterateTimer;
};
