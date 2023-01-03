#ifndef FILELISTMODEL_H
#define FILELISTMODEL_H

#include <QAbstractItemModel>
#include <QSharedPointer>
#include <qqml.h>

// 自定义树节点
struct MyTreeItem {
    // 节点属性
    QString name;
    // 节点位置
    int row;
    // 父节点
    QSharedPointer<MyTreeItem> parentItem;
    // 子节点
    QList<QSharedPointer<MyTreeItem>> subItems;
};

class FileListModel : public QAbstractItemModel
{
    Q_OBJECT
    QML_ELEMENT
public:
    enum RoleType {
        FullNameRole = Qt::UserRole
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
    Q_INVOKABLE void initItems();

private:
    MyTreeItem  *getItem(const QModelIndex &idx) const;

    // 根节点
    QSharedPointer<MyTreeItem> rootItem;
};

#endif // FILELISTMODEL_H
