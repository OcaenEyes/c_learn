#include "duetcpsocket.h"
#include "protocol.h"

DueTcpSocket::DueTcpSocket(QObject *parent)
    : QTcpSocket{parent}
{
    connect(this,SIGNAL(readyRead()),
            this,SLOT(receiveMsg()));
}

void DueTcpSocket::receiveMsg()
{
    qDebug() << this->bytesAvailable();
    uint pduLen = 0;
    this->read((char*)&pduLen ,sizeof(uint));
    uint msgLen = pduLen-sizeof(PDU);
    PDU *pdu = mkPDU(msgLen);
    this->read((char*)pdu + sizeof(uint), pduLen-sizeof(uint));
    qDebug() << pdu->caMsgType <<(char*)(pdu->caMsg);

}
