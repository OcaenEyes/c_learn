#ifndef FILELISTMODEL_H
#define FILELISTMODEL_H

#include <QAbstractItemModel>
#include <QSharedPointer>

class FileListModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit FileListModel(QObject *parent = nullptr);
};

#endif // FILELISTMODEL_H
