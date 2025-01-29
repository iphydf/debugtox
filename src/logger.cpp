/* SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright © 2022 by The qTox Project Contributors
 * Copyright © 2024-2025 The TokTok team.
 */
#include "logger.h"

#include "src/containers/circularbuffer.h"

#include <QDateTime>
#include <QDebug>
#include <QDir>
#include <QMutex>
#include <QMutexLocker>

#include <cstdio>

namespace {
QMutex logMutex;
CircularBuffer<Logger::LogEntry> logMessages{1000};

const QString timestampFormat = QStringLiteral("hh:mm:ss.zzz");

template <typename F>
auto withLogLock(F&& f)
{
    QMutexLocker lock(&logMutex);
    return f();
}

constexpr std::string_view sourceRootPath()
{
    // We're not using QT_MESSAGELOG_FILE here, because that can be 0, NULL, or
    // nullptr in release builds.
    constexpr std::string_view path = __FILE__;
    constexpr size_t srcRootPos = [=]() {
        size_t pos = path.rfind("/src/");
        if (pos == std::string_view::npos) {
            pos = path.rfind("\\src\\");
        }
        return pos;
    }();
    // If this fails, we might not be getting a long enough path from __FILE__.
    // In that case, we'll need to use a different method to find the source root,
    // or only show the filename without the path.
    static_assert(srcRootPos != std::string_view::npos);
    return path.substr(0, srcRootPos);
}

// Clean up the file path to avoid leaking the user's username or build directory structure.
QString canonicalLogFilePath(const char* filename)
{
    QString file = QString::fromUtf8(filename);
    constexpr std::string_view srcPath = sourceRootPath();
    if (file.startsWith(QString::fromUtf8(srcPath.data(), srcPath.size()))) {
        file = file.mid(srcPath.length() + 1);
    }

    // The file path is outside of the project directory, but if it's in the user's $HOME, we should
    // still strip the path to prevent leaking the user's username.
    const auto home = QDir::homePath();
    if (file.startsWith(home)) {
        file = QStringLiteral("~") + file.mid(home.length());
    }

    return file;
}

// Replace the user's home with "~" to prevent leaking the user's username in log messages.
QString canonicalLogMessage(QString msg)
{
    // Replace the user's home with "~" to prevent leaking the user's username in log messages.
    return msg.replace(QDir::homePath(), QStringLiteral("~"));
}

void logMessageHandler(QtMsgType type, const QMessageLogContext& context, const QString& message)
{
    const Logger::LogEntry entry{
        QDateTime::currentDateTimeUtc(),
        QString::fromUtf8(context.category),
        canonicalLogFilePath(context.file),
        context.line,
        type,
        canonicalLogMessage(message),
    };
    std::fprintf(stderr, "%s\n", Logger::format(entry).toLocal8Bit().constData());

    withLogLock([&] { logMessages.push(entry); });
}
} // namespace

QString Logger::format(QtMsgType type)
{
    switch (type) {
    case QtDebugMsg:
        return QStringLiteral("Debug");
    case QtInfoMsg:
        return QStringLiteral("Info");
    case QtWarningMsg:
        return QStringLiteral("Warning");
    case QtCriticalMsg:
        return QStringLiteral("Critical");
    case QtFatalMsg:
        return QStringLiteral("Fatal");
    }
    return QStringLiteral("Unknown");
}

QString Logger::format(const QDateTime& timestamp)
{
    return timestamp.toString(timestampFormat);
}

QString Logger::format(const LogEntry& entry)
{
    return QStringLiteral("[%1] (%2) %3:%4 : %5: %6")
        .arg(format(entry.timestamp))
        .arg(entry.category)
        .arg(entry.file)
        .arg(entry.line)
        .arg(format(entry.type))
        .arg(entry.message);
}

void Logger::install()
{
    qInstallMessageHandler(logMessageHandler);
}

QList<Logger::LogEntry> Logger::logSnapshot()
{
    return withLogLock([] { return logMessages.toList(); });
}

void Logger::resizeLog(std::size_t size)
{
    withLogLock([&] { logMessages.resize(size); });
}

std::size_t Logger::logCapacity()
{
    return withLogLock([] { return logMessages.capacity(); });
}
