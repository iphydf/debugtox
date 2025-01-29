/* SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright © 2025 The TokTok team.
 */
#pragma once

#include <QList>
#include <QMainWindow>

#include <memory>

namespace Ui {
class DebugTox;
}

class DebugTox : public QMainWindow
{
    Q_OBJECT

public:
    explicit DebugTox(QWidget* parent = nullptr);
    ~DebugTox() override;

private slots:
    void on_actionExit_triggered();

private:
    std::unique_ptr<Ui::DebugTox> ui;
};
