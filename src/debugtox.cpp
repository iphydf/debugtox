/* SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright © 2025 The TokTok team.
 */
#include "debugtox.h"

#include "ui_debugtox.h"

#include "src/views/commandview.h"

DebugTox::DebugTox(QWidget* parent)
    : QMainWindow(parent)
    , ui(std::make_unique<Ui::DebugTox>())
{
    ui->setupUi(this);

    connect(ui->commandView, &CommandView::statusUpdate, this,
            [this](const QString& status) { ui->statusbar->showMessage(status); });

    ui->commandView->setStatus(QStringLiteral("ready"));
}

DebugTox::~DebugTox() = default;

void DebugTox::on_actionExit_triggered()
{
    close();
}
