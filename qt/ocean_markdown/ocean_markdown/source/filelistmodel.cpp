#include "filelistmodel.h"
#include <QDebug>
#include <QDir>
#include <QFileInfoList>
#include <QFileInfo>


FileListModel::FileListModel(QObject *parent) : QAbstractItemModel(parent),rootItem(new MyTreeItem)
{
}

QModelIndex FileListModel::index(int row,int column,const QModelIndex &parent) const{
    if(!hasIndex(row,column,parent)){
        return QModelIndex();
    }
    MyTreeItem* parentItem = getItem(parent);
    auto childPtr = parentItem->subItems.at(row);
    if(childPtr){
        return createIndex(row,column,childPtr.get());
    }else{
        return QModelIndex();
    }
}

QModelIndex FileListModel::parent(const QModelIndex &index) const{
    if(!index.isValid()){
        return QModelIndex();
    }
    MyTreeItem *childItem = getItem(index);
    auto parentPtr = childItem ->parentItem;
    if(!parentPtr || parentPtr == rootItem){
        return QModelIndex();
    }
    return createIndex(parentPtr.get()->row,0,parentPtr.get());
}

int FileListModel::rowCount(const QModelIndex &parent) const{
    MyTreeItem *parentItem = getItem(parent);
    return parentItem->subItems.size();
}

int FileListModel::columnCount(const QModelIndex &parent) const{
//    Q_UNUSED(parent);
    return 1;
}

QVariant FileListModel::data(const QModelIndex &index,int role) const{
//    qDebug() << "在初始化数据了node" << Qt::endl;
    if(!index.isValid()){
        return QVariant();
    }
    MyTreeItem *item = getItem(index);
    if(role == Qt::DisplayRole) {
        //TreeView继承自TableView，所以可以通过不同的column来取单元格数据
        role = Qt::UserRole + index.column();
    }
    switch (role) {
        case FullNameRole:
            return item->name;
        case FullPathRole:
            return item->fPath;
        default: break;
    }
    return QVariant();

}

QHash<int,QByteArray> FileListModel::roleNames() const{
    QHash<int, QByteArray> names = QAbstractItemModel::roleNames();
    names.insert(QHash<int, QByteArray>{
                     {FullNameRole, "name"},
                     {FullPathRole,"fPath"}
                 });
    return names;
}

MyTreeItem *FileListModel::getItem(const QModelIndex &idx) const{
    if(idx.isValid()){
        MyTreeItem *item = static_cast<MyTreeItem*>(idx.internalPointer());
        if(item){
            return item;
        }
    }
    return rootItem.get();
}

void FileListModel::getFullFileAndFolder(QString dirPath,QSharedPointer<MyTreeItem> itemNode){
    QDir _dir(dirPath);
    if (!_dir.exists()){
        _dir.mkdir(dirPath);
    }
    _dir.setSorting(QDir::DirsFirst);
    QFileInfoList _tempFileInfoList =  _dir.entryInfoList(QDir::Dirs | QDir::Files |QDir::NoDotAndDotDot);
    QFileInfo _tempFileInfo;

    foreach (_tempFileInfo, _tempFileInfoList) {
        QSharedPointer<MyTreeItem> _level{new MyTreeItem};
        _level->parentItem = itemNode;
        itemNode->subItems.append(_level);
        _level->row = _tempFileInfoList.indexOf(_tempFileInfo);
        _level->name = _tempFileInfo.fileName();
        _level->fPath = _tempFileInfo.absoluteFilePath();
        if(_tempFileInfo.isDir()){
            getFullFileAndFolder(_tempFileInfo.absoluteFilePath(),_level);
        }else{
            qDebug() << "fileName="<<_tempFileInfo.fileName()
                     << "absoluteFilePath="<< _tempFileInfo.absoluteFilePath()
                     <<"fileSize="<<_tempFileInfo.size()
                     << "lastModified=" << _tempFileInfo.lastModified().toString("yyyy-MM-dd hh:mm:ss");
        }
    }
}


void FileListModel::initItems(QString dirPath){
    rootItem->subItems.clear();
    beginResetModel();
    #ifdef Q_OS_WIN
        dirPath = dirPath.remove("file:///");
    #endif

    #ifdef Q_OS_MAC
        dirPath = dirPath.remove("file://");
    #endif

    #ifdef Q_OS_LINUX
        dirPath = dirPath.remove("file://");
    #endif

    QDir _dir(dirPath);
    if (!_dir.exists()){
        _dir.mkdir(dirPath);
    }
    getFullFileAndFolder(dirPath,rootItem);
//    for(int i=0; i<10; i++)
//        {
//            QSharedPointer<MyTreeItem> lv1{new MyTreeItem};
//            lv1->parentItem = rootItem;
//            rootItem->subItems.append(lv1);
//            lv1->row = i;
//            lv1->name = QString("lv1-%1").arg(i);
//            for(int j=0; j<10; j++)
//            {
//                QSharedPointer<MyTreeItem> lv2{new MyTreeItem};
//                lv2->parentItem = lv1;
//                lv1->subItems.append(lv2);
//                lv2->row = j;
//                lv2->name = QString("lv2-%1-%2").arg(i).arg(j);
//            }
//    }
    endResetModel();
    qDebug()<<__FUNCTION__<<rowCount()<<columnCount();
    qDebug() << "打开文件夹rootItem：" << rootItem->subItems <<Qt::endl;
}


void FileListModel::initItem(QString filePath){
    rootItem->subItems.clear();
    beginResetModel();
    #ifdef Q_OS_WIN
        filePath = filePath.remove("file:///");
    #endif

    #ifdef Q_OS_MAC
        filePath = filePath.remove("file://");
    #endif

    #ifdef Q_OS_LINUX
        filePath = filePath.remove("file://");
    #endif

    QFileInfo _tempFileInfo(filePath);
    QSharedPointer<MyTreeItem> _level{new MyTreeItem};
    _level->parentItem= rootItem;
    rootItem->subItems.append(_level);
    _level->row = 0;
    _level->name = _tempFileInfo.fileName();
    _level->fPath = _tempFileInfo.absoluteFilePath();

    qDebug() << "fileName="<<_tempFileInfo.fileName()
             << "absoluteFilePath="<< _tempFileInfo.absoluteFilePath()
             <<"fileSize="<<_tempFileInfo.size()
             << "lastModified=" << _tempFileInfo.lastModified().toString("yyyy-MM-dd hh:mm:ss");

    endResetModel();
    qDebug()<<__FUNCTION__<<rowCount()<<columnCount();
    qDebug() << "打开文档rootItem：" << rootItem->subItems <<Qt::endl;

}


void FileListModel::appendChild(const QModelIndex &index){
    index.internalPointer();
}

void FileListModel::removeChild(int row,int count , QModelIndex _item){

}
