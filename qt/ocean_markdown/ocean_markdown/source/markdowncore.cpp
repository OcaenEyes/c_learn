#include "markdowncore.h"
#include <QDebug>
#include <QDir>
#include <QList>

MarkDownCore::MarkDownCore(QObject *parent)
    : QObject{parent}
{
    connect(this,SIGNAL(fileNameChanged()),this,SLOT(readFileContent()));
}

QString MarkDownCore::markdown(){
    return _textIn;
}

void MarkDownCore::markdownIn(const QString &_text){
    if(_text == _textIn){
        return;
    }

    qDebug() << "有新的文本输入,内容是："<< _textIn << Qt::endl;

    QFile file(_fName);
    _textIn= _text;
    if(!file.open(QIODevice::WriteOnly)){
        qDebug() << "文件写入失败，请重试"<< Qt::endl;
    }else{
        QTextStream out(&file);
        out<<_textIn;
        file.close();
    }

    emit textInChanged();
}

QString MarkDownCore::getFileName(){
    return _fName;
}
void MarkDownCore::setFileName(const QString &_fileName){
    _fName = _fileName;
    qDebug() << "文件路径变化了，是："<< _fileName << Qt::endl;
    emit fileNameChanged();
}


void MarkDownCore::readFileContent(){
    QFile file(_fName);
    if(!file.open(QIODevice::ReadOnly)){
        _textIn= "> 文件打开失败，请重试";
    }
    _textIn.clear();
    _textIn = file.readAll();
    qDebug() << "开始读取新文件，内容是："<< _textIn << Qt::endl;
    emit textInChanged();
}

