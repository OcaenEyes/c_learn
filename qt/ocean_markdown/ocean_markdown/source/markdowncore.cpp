#include "markdowncore.h"
#include <QDebug>
#include <QDir>
#include <QList>
#include "filelistmodel.h"

MarkDownCore::MarkDownCore(QObject *parent)
    : QObject{parent}
{

}

QString MarkDownCore::markdown(){
    return _textIn;
}

void MarkDownCore::markdownIn(const QString &_text){
    if(_text == _textIn){
        return;
    }
    _textIn= _text;
    qDebug() << "有新的文本输入,内容是："<< _textIn << Qt::endl;
    emit hasMarkdownIn();
}

std::vector<QString> MarkDownCore::getFileList(QString dir){
    qDebug() << dir << Qt::endl;
    dir = dir.remove("file://");
    std::vector<QString> filePath;
    QDir dirPath(dir);
    qDebug() << dirPath << Qt::endl;

    if(!dirPath.exists())
        qDebug() << "dirPath不存在" << Qt::endl;

    QFileInfoList fileInfoList = dirPath.entryInfoList(QDir::Files | QDir::NoDotAndDotDot | QDir::Dirs);
    qDebug() << fileInfoList << Qt::endl;

    QString name = "";

    FileListModel _filelistModel;

    for (auto it = fileInfoList.begin(); it != fileInfoList.end(); ++it) {
        qDebug() << "it是："<< *it << Qt::endl;
        name = it->fileName();
        if(it->isDir()){

        }
        filePath.push_back(name);
    }
    qDebug() << filePath << Qt::endl;

    return filePath;
}
