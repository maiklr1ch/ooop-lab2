#include "databasemanager.h"

DatabaseManager::DatabaseManager() {
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("files.db");

    if (!database.open())
        qFatal("Не вдалося відкрити базу даних!");

    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS files ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "name TEXT, "
               "path TEXT UNIQUE, "
               "metadata TEXT)");
}

DatabaseManager& DatabaseManager::instance() {
    static DatabaseManager instance;
    return instance;
}

void DatabaseManager::addFile(const QString& filePath) {
    QFileInfo fileInfo(filePath);

    QSqlQuery query;
    query.prepare("INSERT INTO files (name, path, metadata) VALUES (?, ?, ?)");
    query.addBindValue(fileInfo.fileName());
    query.addBindValue(fileInfo.absoluteFilePath());
    query.addBindValue("");
    query.exec();
}

void DatabaseManager::deleteFile(const QString& filePath) {
    QSqlQuery query;
    query.prepare("DELETE FROM files WHERE path = ?");
    query.addBindValue(filePath);
    query.exec();
}

void DatabaseManager::updateMetadata(const QString& filePath, const QString& metadata) {
    QSqlQuery query;
    query.prepare("UPDATE files SET metadata = ? WHERE path = ?");
    query.addBindValue(metadata);
    query.addBindValue(filePath);
    query.exec();
}

QList<FileInfo> DatabaseManager::getFiles() {
    QList<FileInfo> files;
    QSqlQuery query("SELECT name, path, metadata FROM files");

    while (query.next()) {
        FileInfo file;
        file.name = query.value(0).toString();
        file.path = query.value(1).toString();
        file.metadata = query.value(2).toString();
        files.append(file);
    }

    return files;
}
