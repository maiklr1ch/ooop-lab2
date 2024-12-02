#include "metadataeditor.h"
#include "ui_metadataeditor.h"
#include "databasemanager.h"
#include <QMessageBox>

MetadataEditor::MetadataEditor(const QString& filePath, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MetadataEditor),
    filePath(filePath)
{
    ui->setupUi(this);
    setWindowTitle("Файловий менеджер | Редагувати метадані");

    // Завантаження існуючих метаданих
    auto files = DatabaseManager::instance().getFiles();
    for (const auto& file : files) {
        if (file.path == filePath) {
            ui->metadataTextEdit->setPlainText(file.metadata);
            break;
        }
    }

    connect(ui->saveButton, &QPushButton::clicked, this, &MetadataEditor::saveMetadata);
    connect(ui->cancelButton, &QPushButton::clicked, this, &QDialog::reject);
}

MetadataEditor::~MetadataEditor() {
    delete ui;
}

void MetadataEditor::saveMetadata() {
    QString metadata = ui->metadataTextEdit->toPlainText();
    DatabaseManager::instance().updateMetadata(filePath, metadata);
    QMessageBox::information(this, "Збережено", "Метадані успішно збережено!");
    accept();
}
