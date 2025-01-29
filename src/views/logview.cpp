/* SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright © 2025 The TokTok team.
 */
#include "logview.h"

#include "ui_logview.h"

#include "src/logger.h"

#include <QSet>
#include <QString>
#include <QStringList>
#include <QTableWidgetItem>

namespace {
const QString allFilterEntry = QStringLiteral("All");
}

LogView::LogView(QWidget* parent)
    : QWidget(parent)
    , ui(std::make_unique<Ui::LogView>())
{
    ui->setupUi(this);

    autoScroll = ui->autoScroll->isChecked();
    ui->logSize->setValue(Logger::logCapacity());

    reload();

    connect(&reloadTimer, &QTimer::timeout, this, &LogView::reload);
    reloadTimer.setInterval(ui->reloadInterval->value() * 1000);
    reloadTimer.start();
}

LogView::~LogView() = default;

void LogView::updateLog()
{
    const QString categoryFilter = ui->categoryFilter->currentText();
    const QString typeFilter = ui->typeFilter->currentText();
    const QRegularExpression fileFilter{ui->fileFilter->text()};
    const QRegularExpression messageFilter{ui->messageFilter->text()};

    if (!fileFilter.isValid() || !messageFilter.isValid()) {
        return;
    }

    ui->logMessages->setRowCount(0);
    for (const auto& entry : snapshot) {
        if (categoryFilter != allFilterEntry && entry.category != categoryFilter) {
            continue;
        }
        const QString typeName = Logger::format(entry.type);
        if (typeFilter != allFilterEntry && typeName != typeFilter) {
            continue;
        }
        if (!fileFilter.pattern().isEmpty() && !fileFilter.match(entry.file).hasMatch()) {
            continue;
        }
        if (!messageFilter.pattern().isEmpty() && !messageFilter.match(entry.message).hasMatch()) {
            continue;
        }

        auto timestamp = std::make_unique<QTableWidgetItem>(Logger::format(entry.timestamp));
        auto category = std::make_unique<QTableWidgetItem>(entry.category);
        auto source = std::make_unique<QTableWidgetItem>(
            QStringLiteral("%1:%2").arg(entry.file).arg(entry.line));
        auto type = std::make_unique<QTableWidgetItem>(typeName);
        auto message = std::make_unique<QTableWidgetItem>(entry.message);

        const int row = ui->logMessages->rowCount();
        ui->logMessages->insertRow(row);
        ui->logMessages->setItem(row, 0, timestamp.release());
        ui->logMessages->setItem(row, 1, category.release());
        ui->logMessages->setItem(row, 2, source.release());
        ui->logMessages->setItem(row, 3, type.release());
        ui->logMessages->setItem(row, 4, message.release());
    }

    ui->logMessages->resizeColumnsToContents();
    ui->logMessages->resizeRowsToContents();

    if (autoScroll) {
        ui->logMessages->scrollToBottom();
    }
}

void LogView::reload()
{
    snapshot = Logger::logSnapshot();

    QSet<QString> categories;
    std::transform(snapshot.begin(), snapshot.end(), std::inserter(categories, categories.end()),
                   [](const Logger::LogEntry& entry) { return entry.category; });
    QSet<QtMsgType> types;
    std::transform(snapshot.begin(), snapshot.end(), std::inserter(types, types.end()),
                   [](const Logger::LogEntry& entry) { return entry.type; });

    const QString categoryFilter = ui->categoryFilter->currentText();
    ui->categoryFilter->clear();
    ui->categoryFilter->addItem(allFilterEntry);
    for (const auto& category : categories) {
        ui->categoryFilter->addItem(category);
    }
    ui->categoryFilter->setCurrentText(categoryFilter.isEmpty() ? allFilterEntry : categoryFilter);

    const QString typeFilter = ui->typeFilter->currentText();
    ui->typeFilter->clear();
    ui->typeFilter->addItem(allFilterEntry);
    for (const auto& type : types) {
        ui->typeFilter->addItem(Logger::format(type));
    }
    ui->typeFilter->setCurrentText(typeFilter.isEmpty() ? allFilterEntry : typeFilter);

    updateLog();
}

void LogView::on_autoReload_stateChanged(int state)
{
    reloadTimer.stop();
}

void LogView::on_autoScroll_stateChanged(int state)
{
    autoScroll = state == Qt::Checked;
}

void LogView::on_reloadInterval_valueChanged(int value)
{
    reloadTimer.setInterval(value * 1000);
}

void LogView::on_logSize_valueChanged(int value)
{
    Logger::resizeLog(value);
}

void LogView::on_categoryFilter_currentIndexChanged(int index)
{
    Q_UNUSED(index);
    updateLog();
}

void LogView::on_typeFilter_currentIndexChanged(int index)
{
    Q_UNUSED(index);
    updateLog();
}

void LogView::on_fileFilter_textChanged(const QString& text)
{
    Q_UNUSED(text);
    updateLog();
}

void LogView::on_messageFilter_textChanged(const QString& text)
{
    Q_UNUSED(text);
    updateLog();
}
