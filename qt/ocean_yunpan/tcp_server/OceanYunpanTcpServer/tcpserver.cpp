#include "tcpserver.h"
#include "./ui_tcpserver.h"
#include "customertcpserver.h"
#include <QFile>
#include <QStringList>
#include <QByteArray>
#include <QMessageBox>

TcpServer::TcpServer(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TcpServer)
{
    ui->setupUi(this);
    loadConfig();
    listenClient();

}

TcpServer::~TcpServer()
{
    delete ui;
}

void TcpServer::listenClient()
{
    CustomerTcpServer::getInstance().listen(
                QHostAddress(m_Ip),m_Port);
}

void TcpServer::loadConfig()
{
    QFile server_conf_file(":/server/server.config");
    if(server_conf_file.open(QIODevice::ReadOnly)){
        QByteArray byteData = server_conf_file.readAll();
        QString strData = byteData.toStdString().c_str();
        QStringList server_conf_list =strData.replace("\r\n"," ").split(" ");
        m_Ip = server_conf_list.at(0);
        m_Port = server_conf_list.at(1).toUInt();
    }else{
        QMessageBox::critical(this,"监听端口","监听端口失败");
    }
}

