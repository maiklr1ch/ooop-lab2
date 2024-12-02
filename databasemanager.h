#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QFileInfo>
#include <QList>

struct FileInfo {
    QString name;
    QString path;
    QString metadata;
};

class DatabaseManager {
public:
    static DatabaseManager& instance();

    void addFile(const QString& filePath);
    void deleteFile(const QString& filePath);
    void updateMetadata(const QString& filePath, const QString& metadata);
    QList<FileInfo> getFiles();

private:
    DatabaseManager();
    QSqlDatabase database;
};

#endif // DATABASEMANAGER_H
