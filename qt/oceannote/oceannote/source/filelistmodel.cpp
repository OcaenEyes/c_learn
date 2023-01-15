#include "filelistmodel.h"
#include <QDebug>
#include <QMessageBox>

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
    showFileDialog(QFileDialog::AcceptMode::AcceptSave,QFileDialog::FileMode::ExistingFile);



}

void FileListModel::saveAsFile(){
    qDebug()<< "点击了文件另存为" << Qt::endl;
    showFileDialog(QFileDialog::AcceptMode::AcceptSave,QFileDialog::FileMode::ExistingFile);

}

void FileListModel::openFile(){
    qDebug()<< "点击了打开文件" << Qt::endl;
    showFileDialog(QFileDialog::AcceptMode::AcceptOpen,QFileDialog::FileMode::ExistingFile);

}

void FileListModel::openFolder(){
    qDebug()<< "点击了打开文件夹" << Qt::endl;
    showFileDialog(QFileDialog::AcceptMode::AcceptOpen,QFileDialog::FileMode::Directory);

}

void FileListModel::openNewWindow(){
    qDebug()<< "点击了打开新窗口" << Qt::endl;
}

QString FileListModel::showFileDialog(QFileDialog::AcceptMode _mode,QFileDialog::FileMode _type){
    QString _res = "";
    QFileDialog _fd;
    _fd.setFileMode(_type);
    _fd.setAcceptMode(_mode);

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
    _fd.open();

    return _res;
}
