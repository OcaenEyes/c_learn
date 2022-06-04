#ifndef DUETCPSOCKET_H
#define DUETCPSOCKET_H

#include <QTcpSocket>

class DueTcpSocket : public QTcpSocket
{
    Q_OBJECT
public:
    explicit DueTcpSocket(QObject *parent = nullptr);

public slots:
    void receiveMsg();
};

#endif // DUETCPSOCKET_H
