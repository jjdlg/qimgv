#pragma once

#include <QDebug>
#include <QString>
#include <QFileInfo>
#include <QDir>
#include <QDateTime>
#include <QStandardPaths>
#include <QtGlobal>

enum FileOpResult {
    SUCCESS,
    DESTINATION_FILE_EXISTS,
    SOURCE_NOT_WRITABLE,
    DESTINATION_NOT_WRITABLE,
    SOURCE_DOES_NOT_EXIST,
    DESTINATION_DOES_NOT_EXIST,
    NOTHING_TO_DO,
    OTHER_ERROR
};

class FileOperations {
public:
    static void copyTo(const QFileInfo &srcFile, const QString &destDirPath, FileOpResult &result);
    static void moveTo(const QFileInfo &srcFile, const QString &destDirPath, FileOpResult &result);
    static void rename(const QFileInfo &srcFile, const QString &newName, FileOpResult &result);
    static void removeFile(const QString &filePath, FileOpResult &result);
    static void moveToTrash(const QString &filePath, FileOpResult &result);

    static QString decodeResult(const FileOpResult &result);

private:
    static bool moveToTrashImpl(const QString &path);
};