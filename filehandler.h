#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <QString>
#include <QDesktopServices>
#include <QUrl>

class FileHandler {
public:
    static void openFile(const QString& filePath);
};

#endif // FILEHANDLER_H
