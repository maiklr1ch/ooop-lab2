#include "filehandler.h"

void FileHandler::openFile(const QString& filePath) {
    QDesktopServices::openUrl(QUrl::fromLocalFile(filePath));
}
