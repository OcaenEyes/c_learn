#include "filelistmodel.h"
#include <QDebug>
#include <QMessageBox>
#include <QStandardPaths>


FileListModel::FileListModel(QObject *parent)
    : QObject{parent}
{

}


void FileListModel::saveFile(){
    qDebug()<< "点击了保存" << Qt::endl;
    showFileDialog(QFileDialog::AcceptMode::AcceptSave,QFileDialog::FileMode::ExistingFile);

}

void FileListModel::ceateFile(){
    qDebug()<< "点击了创建新文件" << Qt::endl;
    QMessageBox::StandardButton ok =  QMessageBox::warning(NULL,tr("提示"),
                              tr("创建新文件？"),
                              QMessageBox::Yes | QMessageBox::Default,
                              QMessageBox::No);
    if (ok == QMessageBox::StandardButton::Yes){
        qDebug()<< "点击的是确认新建文件" << Qt::endl;
    }
    QString _filePath= showFileDialog(QFileDialog::AcceptMode::AcceptSave,QFileDialog::FileMode::ExistingFile);
    QFile _file(_filePath);
    if(!_file.open(QFile::ReadWrite)){
        qDebug()<< "文件打开失败" << Qt::endl;
    }else{
        QTextStream out(&_file);
        out << textData;
        _file.close();
    }
}

void FileListModel::saveAsFile(){
    qDebug()<< "点击了文件另存为" << Qt::endl;
    qDebug()<< "_text:" << textData<< Qt::endl;
    QString _filePath=showFileDialog(QFileDialog::AcceptMode::AcceptSave,QFileDialog::FileMode::ExistingFile);
    QFile _file(_filePath);
    if(!_file.open(QFile::ReadWrite)){
        qDebug()<< "文件打开失败" << Qt::endl;
    }else{
        QTextStream out(&_file);
        out << textData;
        _file.close();
    }
}

void FileListModel::openFile(){
    qDebug()<< "点击了打开文件" << Qt::endl;
    QString _filePath=showFileDialog(QFileDialog::AcceptMode::AcceptOpen,QFileDialog::FileMode::ExistingFile);

    QFile _file(_filePath);
    if(!_file.open(QFile::ReadWrite)){
        qDebug()<< "文件打开失败" << Qt::endl;
    }else{
        QString _text =_file.readAll();
        qDebug()<< "_text:" << _text<< Qt::endl;
        _file.close();
    }
}

void FileListModel::openFolder(){
    qDebug()<< "点击了打开文件夹" << Qt::endl;
    QString _folderPath=showFileDialog(QFileDialog::AcceptMode::AcceptOpen,QFileDialog::FileMode::Directory);
    qDebug()<< "_folderPath:" << _folderPath<< Qt::endl;

}

void FileListModel::openNewWindow(){
    qDebug()<< "点击了打开新窗口" << Qt::endl;
}

QString FileListModel::showFileDialog(QFileDialog::AcceptMode _mode,QFileDialog::FileMode _type){
    QString _res = "";
    QFileDialog _fd;
    _fd.setFileMode(_type);
    _fd.setAcceptMode(_mode);
    _fd.setDirectory(QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation).at(0));


    switch (_type) {
    case QFileDialog::FileMode::Directory:
        _fd.setWindowTitle("文件夹");
        break;
    case QFileDialog::FileMode::ExistingFile:
        _fd.setWindowTitle("文件");
        _fd.setNameFilters({"Markdown files (*.md)","Text files (*.txt)","Any files (*)"});
        break;
    default:
        break;
    }
    if(_fd.exec() == QFileDialog::Accepted){
//        QStringList _tml = _fd.selectedFiles();
//        qDebug() << "选择的内容是："<<_tml << Qt::endl;
//        qDebug() << "选择的内容是："<<_tml.at(0) << Qt::endl;
        _res= _fd.selectedFiles().at(0);
    }else{
        qDebug() << "没有选择任何东西" << Qt::endl;
    }
    return _res;
}
