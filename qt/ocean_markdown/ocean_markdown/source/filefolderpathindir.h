#ifndef FILEFOLDERPATHINDIR_H
#define FILEFOLDERPATHINDIR_H

#include <QObject>

class FileFolderPathInDir : public QObject
{
    Q_OBJECT
public:
    FileFolderPathInDir();

    FileFolderPathInDir(QString dirpath);

    /** 设置目录
     * @brief setDirPath
     * @param dirPath
     */
    void setDirPath(QString dirPath);

    /** 获取指定目录下的文件路径+名称
     * @brief getFilePathNameOfSelDir
     * @param dirPath
     * @return
     */
    Q_INVOKABLE QStringList getFilePathNameOfSelDir(QString dirPath);

    /** 获取在指定目录下的目录的路径
     * @brief getDirPathOfSelDir
     * @param dirPath
     * @return
     */
    QStringList getDirPathOfSelDir(QString dirPath);

    /** 获取指定目录下的文件和目录的全路径
     * @brief getFileAndDirPathNameOfSelDir
     * @param dirPath
     * @return
     */
    QStringList getFileAndDirPathNameOfSelDir(QString dirPath);


    /** 在指定文件夹下的文件数
     * @brief fileConutInSelDir
     * @param dirPath
     * @return
     */
    int fileConutInSelDir(QString dirPath);

    /** 在指定文件夹下的目录数
     * @brief dirCountInSplDir
     * @param dirPath
     * @return
     */
    int dirCountInSelDir(QString dirPath);

    /** 获取指定目录及其子目录下文件的全路径
     * @brief getFilePathNameOfSplAndChildDir
     * @param dirPath
     * @return
     */
    Q_INVOKABLE QStringList getFilePathNameOfSelAndChildDir(QString dirPath);

    /** 获取指定目录及其子目录下的文件夹的全路径
     * @brief getDirPathOfSplAndChildDir
     * @param dirPath
     * @return
     */
    Q_INVOKABLE QStringList getDirPathOfSelAndChildDir(QString dirPath);

    /** 获取指定目录及其子目录下的文件与目录的全路径
     * @brief getFileAndDirPathNameOfSelAndChildDir
     * @param dirPath
     * @return
     */
    Q_INVOKABLE QStringList getFileAndDirPathNameOfSelAndChildDir(QString dirPath);

private:
    QString dirPath;

};

#endif // FILEFOLDERPATHINDIR_H
