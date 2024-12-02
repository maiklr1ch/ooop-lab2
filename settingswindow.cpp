#include "settingswindow.h"
#include "ui_settingswindow.h"
#include <QSettings>
#include <QMessageBox>

SettingsWindow::SettingsWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsWindow)
{
    ui->setupUi(this);
    setWindowTitle("Файловий менеджер | Налаштування");

    // Завантаження налаштувань
    QSettings settings("OfflineFileManager", "App");
    ui->dbPathLineEdit->setText(settings.value("dbPath", "files.db").toString());

    connect(ui->saveButton, &QPushButton::clicked, this, &SettingsWindow::saveSettings);
    connect(ui->cancelButton, &QPushButton::clicked, this, &QDialog::reject);
}

SettingsWindow::~SettingsWindow() {
    delete ui;
}

void SettingsWindow::saveSettings() {
    QSettings settings("OfflineFileManager", "App");
    settings.setValue("dbPath", ui->dbPathLineEdit->text());
    QMessageBox::information(this, "Збережено", "Налаштування успішно збережено!");
    accept();
}
