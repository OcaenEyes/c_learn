#include "operatedb.h"
#include <QMessageBox>
#include <QString>

OperateDB::OperateDB(QObject *parent)
    : QObject{parent}
{
        m_Db = QSqlDatabase::addDatabase("QSQLITE");
}

OperateDB &OperateDB::getInstance()
{
    static OperateDB instance;
    return instance;
}

void OperateDB::initDB()
{
    m_Db.setHostName("localhost");
    m_Db.setDatabaseName("/Users/gaozhiyong/Documents/GitHub/c_learn/qt/ocean_yunpan/tcp_server/OceanYunpanTcpServer/ocean_yunpan.db");
    m_Db.setUserName("root");
    m_Db.setPassword("123456");
    if (m_Db.open()){
        qDebug() << "打开数据库成功";
        QSqlQuery query;
        query.exec("select * from userInfo");
        while (query.next()){
            QString data = QString("%1,%2,%3").arg(query.value(0).toString(),query.value(1).toString(),query.value(2).toString());
            qDebug() << data;
        }

    }else{
        QMessageBox::critical(NULL,"连接数据",m_Db.lastError().text());
    }
}

OperateDB::~OperateDB()
{
    m_Db.close();
}
