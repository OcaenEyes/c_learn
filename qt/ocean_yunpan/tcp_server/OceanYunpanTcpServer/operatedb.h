#ifndef OPERATEDB_H
#define OPERATEDB_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

class OperateDB : public QObject
{
    Q_OBJECT
public:
    explicit OperateDB(QObject *parent = nullptr);
    static OperateDB &getInstance();
    void initDB();
    ~OperateDB();

public slots:

private:
    QSqlDatabase m_Db;

signals:

};

#endif // OPERATEDB_H
