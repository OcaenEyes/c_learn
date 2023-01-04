#ifndef FILEFOLDERNAME_H
#define FILEFOLDERNAME_H
#include <QSharedPointer>
#include <QList>

// 自定义树节点
struct MyTreeItem {
    // 节点属性
    QString name;

    QString fPath;
    // 节点位置
    int row;
    // 父节点
    QSharedPointer<MyTreeItem> parentItem;
    // 子节点
    QList<QSharedPointer<MyTreeItem>> subItems;
};

#endif // FILEFOLDERNAME_H
