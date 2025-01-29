/* SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright © 2025 The TokTok team.
 */
#pragma once

#include <QList>
#include <QMainWindow>

#include <functional>
#include <memory>

class Core;
class CoreOptions;

namespace Ui {
class CommandView;
}

class CommandView : public QWidget
{
    Q_OBJECT

public:
    explicit CommandView(QWidget* parent);
    ~CommandView() override;

signals:
    void statusUpdate(const QString& status);

private:
    void processCommand(const QString& input);

    void setStatus(const QString& status);
    void addItem(const QString& source, const QString& text);

    void previousCommand();
    bool eventFilter(QObject* watched, QEvent* event) override;

private slots:
    void on_inputEdit_returnPressed();
    void on_sendButton_clicked();

private:
    std::unique_ptr<Ui::CommandView> ui;
    std::unique_ptr<CoreOptions> options;
    std::unique_ptr<Core> core;

    struct Command {
        QString name;
        QString description;
        std::function<void(QStringList args)> function;
    };

    QList<Command> commands;

    QString lastSource;
};
