/* SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright © 2025 The TokTok team.
 */
#include "commandview.h"

#include "ui_commandview.h"

#include "src/core.h"
#include "src/coreoptions.h"
#include "src/models/events/dhtgetnodesresponse.h"

#include <QCompleter>
#include <QKeyEvent>
#include <QString>
#include <QStringList>

#include <memory>
#include <tox/tox.h>

namespace {
const QString srcSystem = QStringLiteral("System");
const QString srcUser = QStringLiteral("User");

const QString statusIterating = QStringLiteral("iterating");
const QString statusStopped = QStringLiteral("stopped");

/**
 * Very simple command parser.
 *
 * Similar to shell commands, parts can be in "quotes" or 'quotes' or without
 * quotes. Quotes are removed. Quotes with inner quotes need escaping.
 */
QStringList parseCommand(const QString& input)
{
    QStringList parts;
    QString part;
    // Single quote or double quote. Empty means not currently in quotes.
    QChar inQuotes;
    bool escape = false;

    for (QChar c : input) {
        if (escape) {
            part += c;
            escape = false;
        } else if (c == QLatin1Char('\\')) {
            escape = true;
        } else if (inQuotes.isNull()) {
            if (c == QLatin1Char(' ') || c == QLatin1Char('\t')) {
                if (!part.isEmpty()) {
                    parts.append(part);
                    part.clear();
                }
            } else if (c == QLatin1Char('\'') || c == QLatin1Char('"')) {
                inQuotes = c;
            } else {
                part += c;
            }
        } else if (c == inQuotes) {
            inQuotes = QChar();
        } else {
            part += c;
        }
    }

    if (!part.isEmpty()) {
        parts.append(part);
    }

    return parts;
}

// Turns a list of parts into a list like "[part1, part2, part3]".
QString printCommand(const QStringList& parts)
{
    QStringList result;
    for (QString part : parts) {
        result.append(
            QStringLiteral("\"%1\"").arg(part.replace(QLatin1Char('"'), QStringLiteral("\\\""))));
    }
    return QStringLiteral("[%1]").arg(result.join(QStringLiteral(", ")));
}

// Turns ["part1", "part2", "part3"] into "part1 part2 part3".
QString reconstructCommand(QString command)
{
    QStringList parts;

    if (!command.startsWith(QLatin1Char('[')) || !command.endsWith(QLatin1Char(']'))) {
        return command;
    }

    command = command.mid(1, command.size() - 2);

    bool inQuotes = false;
    QString part;
    for (QChar c : command) {
        if (c == QLatin1Char('"')) {
            inQuotes = !inQuotes;
        } else if (c == QLatin1Char(',') && !inQuotes) {
            parts.append(part.trimmed());
            part.clear();
        } else {
            part += c;
        }
    }

    if (!part.isEmpty()) {
        parts.append(part.trimmed());
    }

    return parts.join(QLatin1Char(' '));
}
} // namespace

CommandView::CommandView(QWidget* parent)
    : QWidget(parent)
    , ui(std::make_unique<Ui::CommandView>())
    , options(std::make_unique<CoreOptions>(this))
    , core(std::make_unique<Core>(options.get(), this))
{
    ui->setupUi(this);

    connect(core.get(), &Core::eventReceived, this, [this](QSharedPointer<CoreEvent> event) {
        if (dynamic_cast<Events::DhtGetNodesResponse*>(event.get()) != nullptr) {
            return;
        }
        addItem(srcSystem, event->toString());
    });

    commands = {
        {
            QStringLiteral("exit"),
            QStringLiteral("Exit the application"),
            [this](QStringList args) { close(); },
        },
        {
            QStringLiteral("version"),
            QStringLiteral("Print the Tox version"),
            [this](QStringList args) {
                addItem(srcSystem, QStringLiteral("Tox Version: %1.%2.%3")
                                       .arg(tox_version_major())
                                       .arg(tox_version_minor())
                                       .arg(tox_version_patch()));
            },
        },
        {
            QStringLiteral("options"),
            QStringLiteral("Print the current Tox_Options contents"),
            [this](QStringList args) {
                addItem(srcSystem, options->toStringList().join(QLatin1Char('\n')));
            },
        },
        {
            QStringLiteral("set"),
            QStringLiteral("Set a Tox_Options value"),
            [this](QStringList args) {
                if (args.empty() || args.size() > 2) {
                    addItem(srcSystem, QStringLiteral("Usage: set <name> [value]"));
                    return;
                }
                const QString result =
                    options->set(args[0], args.size() == 2 ? args[1] : QStringLiteral(""));
                addItem(srcSystem, result);
            },
        },
        {
            QStringLiteral("start"),
            QStringLiteral("Start iterating the Tox instance"),
            [this](QStringList args) {
                setStatus(statusIterating);
                core->start();
            },
        },
        {
            QStringLiteral("stop"),
            QStringLiteral("Stop iterating the Tox instance"),
            [this](QStringList args) {
                setStatus(statusStopped);
                core->stop();
            },
        },
        {
            QStringLiteral("reload"),
            QStringLiteral("Reload the Tox instance with new options"),
            [this](QStringList args) {
                const QString result = core->reload(options.get());
                addItem(srcSystem, result);
            },
        },
        {
            QStringLiteral("address"),
            QStringLiteral("Print the Tox address"),
            [this](QStringList args) {
                addItem(srcSystem, QStringLiteral("Address: %1").arg(core->address()));
            },
        },
        {
            QStringLiteral("secret_key"),
            QStringLiteral("Print the Tox secret key"),
            [this](QStringList args) {
                addItem(srcSystem, QStringLiteral("Secret Key: %1").arg(core->secretKey()));
            },
        },
        {
            QStringLiteral("bootstrap"),
            QStringLiteral("Bootstrap to a node"),
            [this](QStringList args) {
                if (args.size() != 3) {
                    addItem(srcSystem,
                            QStringLiteral("Usage: bootstrap <address> <port> <public_key>"));
                    return;
                }
                const QString result = core->bootstrap(args[0], args[1].toUShort(),
                                                       QByteArray::fromHex(args[2].toUtf8()));
                addItem(srcSystem, result);
            },
        },
        {
            QStringLiteral("add_tcp_relay"),
            QStringLiteral("Add a TCP relay"),
            [this](QStringList args) {
                if (args.size() != 3) {
                    addItem(srcSystem,
                            QStringLiteral("Usage: add_tcp_relay <address> <port> <public_key>"));
                    return;
                }
                const QString result = core->addTcpRelay(args[0], args[1].toUShort(),
                                                         QByteArray::fromHex(args[2].toUtf8()));
                addItem(srcSystem, result);
            },
        },
    };
    std::sort(commands.begin(), commands.end(),
              [](const Command& a, const Command& b) { return a.name < b.name; });

    QStringList completions{QStringLiteral("help")};
    std::transform(commands.begin(), commands.end(), std::back_inserter(completions),
                   [](const Command& cmd) { return cmd.name; });
    completions.sort();
    auto completer = std::make_unique<QCompleter>(completions, this);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    ui->inputEdit->setCompleter(completer.release());

    ui->inputEdit->installEventFilter(this);
    ui->inputEdit->setFocus();
}

CommandView::~CommandView() = default;

void CommandView::setStatus(const QString& status)
{
    qDebug() << "Status:" << status;
    emit statusUpdate(QStringLiteral("Tox Version: %1.%2.%3 - %4")
                          .arg(tox_version_major())
                          .arg(tox_version_minor())
                          .arg(tox_version_patch())
                          .arg(status));
}

void CommandView::processCommand(const QString& input)
{
    QStringList parts = parseCommand(input);
    if (parts.isEmpty()) {
        return;
    }

    addItem(srcUser, printCommand(parts));
    const QString command = parts.takeFirst();

    auto cmd = std::find_if(commands.begin(), commands.end(),
                            [command](const Command& cmd) { return cmd.name == command; });
    if (cmd != commands.end()) {
        cmd->function(parts);
    } else if (command == QStringLiteral("help")) {
        QString help = QStringLiteral("Available commands:");
        for (const Command& cmd : commands) {
            help += QStringLiteral("\n  %1: %2").arg(cmd.name).arg(cmd.description);
        }
        addItem(srcSystem, help);
    } else {
        addItem(srcSystem, QStringLiteral("Unknown command: %1").arg(command));
    }
}

void CommandView::addItem(const QString& source, const QString& text)
{
    QTableWidgetItem* sourceItem =
        lastSource == source ? new QTableWidgetItem() : new QTableWidgetItem(source);
    QTableWidgetItem* textItem = new QTableWidgetItem(text);

    sourceItem->setTextAlignment(Qt::AlignTop | Qt::AlignLeft);
    textItem->setTextAlignment(Qt::AlignTop | Qt::AlignLeft);

    int row = ui->outputTable->rowCount();
    ui->outputTable->insertRow(row);
    ui->outputTable->setItem(row, 0, sourceItem);
    ui->outputTable->setItem(row, 1, textItem);
    ui->outputTable->resizeRowsToContents();
    ui->outputTable->scrollToBottom();

    lastSource = source;
}

void CommandView::previousCommand()
{
    // Find the previous User command.
    for (int i = ui->outputTable->rowCount() - 1; i >= 0; --i) {
        if (ui->outputTable->item(i, 0)->text() == srcUser) {
            ui->inputEdit->setText(reconstructCommand(ui->outputTable->item(i, 1)->text()));
            break;
        }
    }
}

bool CommandView::eventFilter(QObject* watched, QEvent* event)
{
    if (watched == ui->inputEdit && event->type() == QEvent::KeyPress) {
        QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
        if (keyEvent->key() == Qt::Key_Up) {
            previousCommand();
            return true;
        }
        if (keyEvent->key() == Qt::Key_Down) {
            ui->inputEdit->clear();
            return true;
        }
    }

    return QWidget::eventFilter(watched, event);
}

void CommandView::on_inputEdit_returnPressed()
{
    on_sendButton_clicked();
}

void CommandView::on_sendButton_clicked()
{
    QString text = ui->inputEdit->text();
    ui->inputEdit->clear();

    processCommand(text);
}
