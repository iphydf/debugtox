/* SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright © 2025 The TokTok team.
 */
#pragma once

#include <QDateTime>
#include <QList>

namespace Logger {
struct LogEntry
{
    QDateTime timestamp;
    QString category;
    QString file;
    int line;
    QtMsgType type;
    QString message;
};

QString format(QtMsgType type);
QString format(const QDateTime& timestamp);
QString format(const LogEntry& entry);

void install();
QList<LogEntry> logSnapshot();
std::size_t logCapacity();
void resizeLog(std::size_t size);
} // namespace Logger
