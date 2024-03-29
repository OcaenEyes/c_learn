#include "markdowncore.h"
#include <QDebug>
#include <QDir>
#include <QList>

MarkDownCore::MarkDownCore(QObject *parent)
    : QObject{parent}
{
    connect(this,SIGNAL(fileNameChanged()),this,SLOT(readFileContent()));

    connect(this,SIGNAL(newFileNameChanged()),this,SLOT(saveFile()));
}

QString MarkDownCore::markdown(){
    return _textIn;
}

void MarkDownCore::markdownIn(const QString &_text){
    if(_text == _textIn){
        return;
    }

    qDebug() << "有新的文本输入,内容是："<< _textIn << Qt::endl;
    saveFile(_text);
    emit textInChanged();
}

void MarkDownCore::saveFile(const QString &_text){
    QFile file(_fName);
    _textIn= _text;
    if(!file.open(QIODevice::WriteOnly)){
        qDebug() << "文件写入失败，请重试"<< Qt::endl;
    }else{
        QTextStream out(&file);
        out<<_textIn;
        file.close();
    }
}

void MarkDownCore::saveFile(){
    QFile file(_fName);
    if(!file.open(QIODevice::WriteOnly)){
        qDebug() << "文件写入失败，请重试"<< Qt::endl;
    }else{
        QTextStream out(&file);
        out<<_textIn;
        file.close();
    }
}

QString MarkDownCore::getFileName(){
    return _fName;
}
void MarkDownCore::setFileName(const QString &_fileName){
    _fName = _fileName;
    qDebug() << "文件路径变化了，是："<< _fileName << Qt::endl;
    emit fileNameChanged();
}

QString MarkDownCore::getNewFileName(){
    return _fName;
}
void MarkDownCore::setNewFileName(const QString &_fileName){
    _fName = _fileName;
    qDebug() << "文件路径变化了，是："<< _fileName << Qt::endl;
    emit newFileNameChanged();
}


void MarkDownCore::readFileContent(){
    QFile file(_fName);
    if(!file.open(QIODevice::ReadWrite)){
        _textIn= "> 文件打开失败，请重试";
    }
    _textIn.clear();
    _textIn = file.readAll();
//    qDebug() << "开始读取新文件，内容是："<< _textIn << Qt::endl;
    qDebug() << "开始读取新文件" << Qt::endl;
    emit textInChanged();
}

