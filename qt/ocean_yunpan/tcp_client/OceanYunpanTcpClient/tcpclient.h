#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QWidget>
#include <QFile>
#include <QTcpSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class TcpClient; }
QT_END_NAMESPACE

class TcpClient : public QWidget
{
    Q_OBJECT

public:
    TcpClient(QWidget *parent = nullptr);
    ~TcpClient();
    void loadConfig();
    void connectServer();

public slots:
    void connectStatus();

private slots:
    void on_sendMsg_clicked();

private:
    Ui::TcpClient *ui;
    QString m_Ip;
    quint16 m_Port;
    // 连接服务器， 和服务器进行数据交互
    QTcpSocket m_tcpSocket ;
};
#endif // TCPCLIENT_H
