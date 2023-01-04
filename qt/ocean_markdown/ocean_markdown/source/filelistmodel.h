#ifndef FILELISTMODEL_H
#define FILELISTMODEL_H

#include <QAbstractItemModel>
#include <QSharedPointer>
#include <qqml.h>
#include "filefoldername.h"


class FileListModel : public QAbstractItemModel
{
    Q_OBJECT
    QML_ELEMENT
public:
    enum RoleType {
        FullNameRole = Qt::UserRole,
        FullPathRole
    };

    Q_ENUM(RoleType)

    explicit FileListModel(QObject *parent = nullptr);

    virtual QModelIndex index(int row,int column,const QModelIndex &parent = QModelIndex()) const;

    virtual QModelIndex parent(const QModelIndex &index) const;

    virtual int rowCount(const QModelIndex &parent=QModelIndex()) const;

    virtual int columnCount(const QModelIndex &parent=QModelIndex()) const;

    virtual QVariant data(const QModelIndex &index,int role=Qt::DisplayRole) const;

    virtual QHash<int,QByteArray> roleNames() const;

    // 初始化数据
    Q_INVOKABLE void initItems(QString dirPath);

private:
    MyTreeItem  *getItem(const QModelIndex &idx) const;

    // 根节点
    QSharedPointer<MyTreeItem> rootItem;

    // 遍历文件夹和文件
    void getFullFileAndFolder(QString dirPath, QSharedPointer<MyTreeItem> itemNode);

    int getFullFileAndFolderTimes = 1;

};

#endif // FILELISTMODEL_H
