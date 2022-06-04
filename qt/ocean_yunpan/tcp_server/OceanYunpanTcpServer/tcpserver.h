#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class TcpServer; }
QT_END_NAMESPACE

class TcpServer : public QWidget
{
    Q_OBJECT

public:
    TcpServer(QWidget *parent = nullptr);
    ~TcpServer();

    void listenClient();
    void loadConfig();

private:
    Ui::TcpServer *ui;
    QString m_Ip;
    quint16 m_Port;
};
#endif // TCPSERVER_H
