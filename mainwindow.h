#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "databasemanager.h"
#include "filehandler.h"
#include "metadataeditor.h"
#include "adddialog.h"
#include "settingswindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void addFile();
    void editMetadata();
    void deleteFile();
    void openFile();
    void loadFiles();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
