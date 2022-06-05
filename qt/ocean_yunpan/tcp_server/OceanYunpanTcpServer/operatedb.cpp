#include "operatedb.h"

OperateDB::OperateDB(QObject *parent)
    : QObject{parent}
{

}

OperateDB &OperateDB::getInstance()
{
    static OperateDB instance;
    return instance;
}
