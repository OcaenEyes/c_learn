#include "filefolderpathindir.h"
#include <QDir>
#include <QFileInfo>
#include <QFileInfoList>
#include <QDebug>

FileFolderPathInDir::FileFolderPathInDir()
{
}


FileFolderPathInDir::FileFolderPathInDir(QString dirPath)
{
    dirPath = dirPath.remove("file://");
    this->dirPath = dirPath;
}

/** 设置目录
 * @brief setDirPath
 * @param dirPath
 */
void FileFolderPathInDir::setDirPath(QString dirPath){
    dirPath = dirPath.remove("file://");
    QDir _dir(dirPath);
    if (!_dir.exists()){
        _dir.mkdir(dirPath);
    }
    this->dirPath = dirPath;
}

/** 获取指定目录下的文件路径+名称
 * @brief getFilePathNameOfSelDir
 * @param dirPath
 * @return
 */
QStringList FileFolderPathInDir::getFilePathNameOfSelDir(QString dirPath){
    dirPath = dirPath.remove("file://");
    QDir _dir(dirPath);
    if (!_dir.exists()){
        _dir.mkdir(dirPath);
    }
    QStringList filePathNames;
    QDir selDir(dirPath);
    QFileInfoList fileInfoListInSelDir = selDir.entryInfoList(QDir::Files);
    QFileInfo _tmpFileInfo;
    foreach (_tmpFileInfo, fileInfoListInSelDir) {
        filePathNames << _tmpFileInfo.absoluteFilePath();
    }
    return filePathNames;
}

/** 获取在指定目录下的目录的路径
 * @brief getDirPathOfSelDir
 * @param dirPath
 * @return
 */
QStringList FileFolderPathInDir::getDirPathOfSelDir(QString dirPath){
    dirPath = dirPath.remove("file://");
    QDir _dir(dirPath);
    if (!_dir.exists()){
        _dir.mkdir(dirPath);
    }
    QStringList dirPaths;
    QDir selDir(dirPath);
    QFileInfoList dirsInfoListInSelDir = selDir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);
    QFileInfo _tmpFileInfo;
    foreach (_tmpFileInfo, dirsInfoListInSelDir) {
        dirPaths << _tmpFileInfo.absoluteFilePath();
    }
    return dirPaths;
}

/** 获取指定目录下的文件和目录的全路径
 * @brief getFileAndDirPathNameOfSelDir
 * @param dirPath
 * @return
 */
QStringList FileFolderPathInDir::getFileAndDirPathNameOfSelDir(QString dirPath){
    QStringList  fileAndDirPathNames;
    fileAndDirPathNames << getDirPathOfSelDir(dirPath);
    fileAndDirPathNames << getFilePathNameOfSelDir(dirPath);
    return fileAndDirPathNames;
}


/** 在指定文件夹下的文件数
 * @brief fileConutInSelDir
 * @param dirPath
 * @return
 */
int FileFolderPathInDir::fileConutInSelDir(QString dirPath){
    dirPath = dirPath.remove("file://");
    QDir _dir(dirPath);
    if (!_dir.exists()){
        _dir.mkdir(dirPath);
    }
    return QDir(dirPath).entryInfoList(QDir::Files).count();
}

/** 在指定文件夹下的目录数
 * @brief dirCountInSplDir
 * @param dirPath
 * @return
 */
int FileFolderPathInDir::dirCountInSelDir(QString dirPath){
    dirPath = dirPath.remove("file://");
    QDir _dir(dirPath);
    if (!_dir.exists()){
        _dir.mkdir(dirPath);
    }
    return QDir(dirPath).entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot).count();
}

/** 获取指定目录及其子目录下文件的全路径
 * @brief getFilePathNameOfSplAndChildDir
 * @param dirPath
 * @return
 */
QStringList FileFolderPathInDir::getFilePathNameOfSelAndChildDir(QString dirPath){
    QStringList filePathNames;
    // 首先，得到这个目录下面的文件全部
    filePathNames << getFilePathNameOfSelDir(dirPath);
    // 扫描子目录
    QStringList childDirs;
    childDirs << getDirPathOfSelDir(dirPath);

    QString _tempChildDir;
    foreach (_tempChildDir, childDirs) {
        filePathNames << getFilePathNameOfSelAndChildDir(_tempChildDir);
    }
    return filePathNames;
}

/** 获取指定目录及其子目录下的文件夹的全路径
 * @brief getDirPathOfSplAndChildDir
 * @param dirPath
 * @return
 */
QStringList FileFolderPathInDir::getDirPathOfSelAndChildDir(QString dirPath){
    QStringList dirPaths;
    dirPaths << getDirPathOfSelDir(dirPath);
    qDebug() <<"dirPaths是：" << dirPaths << Qt::endl;
    QString _tempChildDir;
    foreach (_tempChildDir, dirPaths) {
        qDebug() <<"此时_tempChildDir是" << _tempChildDir << Qt::endl;
        dirPaths << getDirPathOfSelAndChildDir(_tempChildDir);
    }
    return dirPaths;
}

/** 获取指定目录及其子目录下的文件与目录的全路径
 * @brief getFileAndDirPathNameOfSelAndChildDir
 * @param dirPath
 * @return
 */
QStringList FileFolderPathInDir::getFileAndDirPathNameOfSelAndChildDir(QString dirPath){
    QStringList fileAndDirPathNames;
    QStringList childDirs;
    childDirs << getDirPathOfSelDir(dirPath);
    QString _tempChildDir;
    foreach (_tempChildDir, childDirs) {
        fileAndDirPathNames<< _tempChildDir;

        // 取其子文件夹的内容
        fileAndDirPathNames << getFileAndDirPathNameOfSelAndChildDir(_tempChildDir);
    }
    fileAndDirPathNames << getFilePathNameOfSelDir(dirPath);
    return fileAndDirPathNames;
}
