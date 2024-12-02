#include "adddialog.h"
#include "ui_adddialog.h"
#include "databasemanager.h"
#include <QFileDialog>
#include <QMessageBox>

AddDialog::AddDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddDialog)
{
    ui->setupUi(this);
    setWindowTitle("Файловий менеджер | Додати файл");

    connect(ui->browseButton, &QPushButton::clicked, this, &AddDialog::selectFile);
    connect(ui->addButton, &QPushButton::clicked, this, &AddDialog::addFile);
    connect(ui->cancelButton, &QPushButton::clicked, this, &QDialog::reject);
}

AddDialog::~AddDialog() {
    delete ui;
}

void AddDialog::selectFile() {
    selectedFilePath = QFileDialog::getOpenFileName(this, "Виберіть файл");
    if (!selectedFilePath.isEmpty()) {
        ui->filePathLineEdit->setText(selectedFilePath);
    }
}

void AddDialog::addFile() {
    if (selectedFilePath.isEmpty()) {
        QMessageBox::warning(this, "Помилка", "Будь ласка, виберіть файл!");
        return;
    }

    DatabaseManager::instance().addFile(selectedFilePath);
    QMessageBox::information(this, "Успіх", "Файл успішно додано!");
    accept();
}
