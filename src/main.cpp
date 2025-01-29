/* SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright © 2025 The TokTok team.
 */
#include "debugtox.h"
#include "logger.h"

#include <QApplication>
#include <QDateTime>
#include <QDebug>

int main(int argc, char* argv[])
{
    Logger::install();
    QApplication a(argc, argv);

    qDebug() << "Starting up...";
    DebugTox w;
    w.show();
    return QApplication::exec();
}
