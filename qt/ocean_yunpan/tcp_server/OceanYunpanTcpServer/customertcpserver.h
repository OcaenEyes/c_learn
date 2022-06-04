#ifndef CUSTOMERTCPSERVER_H
#define CUSTOMERTCPSERVER_H

#include <QTcpServer>
#include <QList>
#include "duetcpsocket.h"

class CustomerTcpServer : public QTcpServer
{
    Q_OBJECT
public:
    CustomerTcpServer();
    static CustomerTcpServer &getInstance();
    void incomingConnection(qintptr socketDescriptor);

private:
    QList<DueTcpSocket*> dueTcpSocket_list;
};

#endif // CUSTOMERTCPSERVER_H
