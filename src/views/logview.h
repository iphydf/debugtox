/* SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright © 2025 The TokTok team.
 */
#pragma once

#include <QTimer>
#include <QWidget>

#include <memory>

namespace Ui {
class LogView;
}

namespace Logger {
struct LogEntry;
}

class LogView final : public QWidget
{
    Q_OBJECT

public:
    explicit LogView(QWidget* parent);
    ~LogView() override;

private:
    void updateLog();
    void reload();

private slots:
    void on_autoReload_stateChanged(int state);
    void on_autoScroll_stateChanged(int state);
    void on_reloadInterval_valueChanged(int value);
    void on_logSize_valueChanged(int value);
    void on_categoryFilter_currentIndexChanged(int index);
    void on_typeFilter_currentIndexChanged(int index);
    void on_fileFilter_textChanged(const QString& text);
    void on_messageFilter_textChanged(const QString& text);

private:
    std::unique_ptr<Ui::LogView> ui;

    QList<Logger::LogEntry> snapshot;
    QTimer reloadTimer;
    bool autoScroll;
};
