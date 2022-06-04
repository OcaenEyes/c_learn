#include "tcpclient.h"
#include "./ui_tcpclient.h"
#include <QByteArray>
#include <QDebug>
#include <QMessageBox>
#include <QStringList>
#include "protocol.h"

TcpClient::TcpClient(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TcpClient)
{
    ui->setupUi(this);
    loadConfig();
    connectServer();
}

TcpClient::~TcpClient()
{
    delete ui;
}

void TcpClient::loadConfig()
{
    QFile client_conf_file(":/client/client.config");
    if(client_conf_file.open(QIODevice::ReadOnly)){
        QByteArray byteData =  client_conf_file.readAll();
        QString strData = byteData.toStdString().c_str();
        qDebug() << strData;
        client_conf_file.close();

        strData.replace("\r\n"," ");
//        qDebug() << strData;
        QStringList conf_list = strData.split(" ");
//        for(int i=0;i <conf_list.size();i++){
//            qDebug() << "size";
//            qDebug() << conf_list[i];
//        }

//        for(int i=0;i <conf_list.length();i++){
//            qDebug() << "length";
//            qDebug() << conf_list[i];
//        }
       m_Ip =  conf_list.at(0);
       m_Port =  conf_list.at(1).toUShort();

    }else{
        QMessageBox::critical(this,"加载配置","加载配置失败");
    }

}

void TcpClient::connectServer()
{
    connect(&m_tcpSocket,SIGNAL(connected()), this, SLOT(connectStatus()));
    m_tcpSocket.connectToHost(
                QHostAddress(m_Ip),m_Port);
}

void TcpClient::connectStatus()
{
    QMessageBox::information(this,"服务器连接状态","服务器连接成功");
}


void TcpClient::on_sendMsg_clicked()
{
    QString strMsg = ui->lineEdit->text();
    if (!strMsg.isEmpty()){
        PDU *pdu = mkPDU(strMsg.size());
        pdu->caMsgType = 1;
        memcpy(pdu->caMsg,strMsg.toStdString().c_str(),strMsg.size());
        qDebug() << pdu->caMsg;
        m_tcpSocket.write((char*)pdu, pdu->caPDULen);
        free(pdu);
        pdu = NULL;

    }else{
        QMessageBox::warning(this,"","消息内容未空");
    }
}

