#ifndef ADDDIALOG_H
#define ADDDIALOG_H

#include <QDialog>

namespace Ui {
class AddDialog;
}

class AddDialog : public QDialog {
    Q_OBJECT

public:
    explicit AddDialog(QWidget *parent = nullptr);
    ~AddDialog();

private slots:
    void selectFile();
    void addFile();

private:
    Ui::AddDialog *ui;
    QString selectedFilePath;
};

#endif // ADDDIALOG_H
