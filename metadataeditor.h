#ifndef METADATAEDITOR_H
#define METADATAEDITOR_H

#include <QDialog>

namespace Ui {
class MetadataEditor;
}

class MetadataEditor : public QDialog {
    Q_OBJECT

public:
    explicit MetadataEditor(const QString& filePath, QWidget *parent = nullptr);
    ~MetadataEditor();

private slots:
    void saveMetadata();

private:
    Ui::MetadataEditor *ui;
    QString filePath;
};

#endif // METADATAEDITOR_H
