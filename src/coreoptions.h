/* SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright © 2025 The TokTok team.
 */
#pragma once

#include <QObject>

#include <memory>
#include <qcontainerfwd.h>

struct Tox_Options;

class Tox_Options_Deleter
{
public:
    void operator()(Tox_Options* options) const;
};

class CoreOptions : public QObject
{
    Q_OBJECT

public:
    explicit CoreOptions(QObject* parent = nullptr);
    ~CoreOptions() override;

    const Tox_Options* get() const;

    QStringList toStringList() const;

    void setSavedata(const QByteArray& savedata);

    QString set(const QString& name, const QString& value);

private:
    std::unique_ptr<Tox_Options> options;
};
