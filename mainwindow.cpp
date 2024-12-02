#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Файловий менеджер");

    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->setHorizontalHeaderLabels({"Назва", "Шлях", "Метадані"});

    connect(ui->addButton, &QPushButton::clicked, this, &MainWindow::addFile);
    connect(ui->editButton, &QPushButton::clicked, this, &MainWindow::editMetadata);
    connect(ui->deleteButton, &QPushButton::clicked, this, &MainWindow::deleteFile);
    connect(ui->openButton, &QPushButton::clicked, this, &MainWindow::openFile);
    connect(ui->settingsButton, &QAction::triggered, this, []() {
        SettingsWindow settings;
        settings.exec();
    });

    loadFiles();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::addFile() {
    AddDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        loadFiles();
    }
}

void MainWindow::editMetadata() {
    int currentRow = ui->tableWidget->currentRow();
    if (currentRow == -1)
        return;

    QString filePath = ui->tableWidget->item(currentRow, 1)->text();
    MetadataEditor editor(filePath, this);
    if (editor.exec() == QDialog::Accepted) {
        loadFiles();
    }
}

void MainWindow::deleteFile() {
    int currentRow = ui->tableWidget->currentRow();
    if (currentRow == -1)
        return;

    QString filePath = ui->tableWidget->item(currentRow, 1)->text();
    DatabaseManager::instance().deleteFile(filePath);
    loadFiles();
}

void MainWindow::openFile() {
    int currentRow = ui->tableWidget->currentRow();
    if (currentRow == -1)
        return;

    QString filePath = ui->tableWidget->item(currentRow, 1)->text();
    FileHandler::openFile(filePath);
}

void MainWindow::loadFiles() {
    ui->tableWidget->setRowCount(0);

    auto files = DatabaseManager::instance().getFiles();
    for (const auto &file : files) {
        int row = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(row);
        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(file.name));
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(file.path));
        ui->tableWidget->setItem(row, 2, new QTableWidgetItem(file.metadata));
    }
}
