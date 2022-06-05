#include "customertcpserver.h"

CustomerTcpServer::CustomerTcpServer()
{

}

CustomerTcpServer &CustomerTcpServer::getInstance()
{
    static CustomerTcpServer instance;
    return instance;
}

void CustomerTcpServer::incomingConnection(qintptr socketDescriptor)
{
    qDebug() << "有新的连接来了";
    DueTcpSocket *dueTcpSocket = new DueTcpSocket();
    dueTcpSocket->setSocketDescriptor(socketDescriptor);
    dueTcpSocket_list.append(dueTcpSocket);
}
