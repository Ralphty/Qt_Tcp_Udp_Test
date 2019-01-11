#ifndef UDPRECEIVER_H
#define UDPRECEIVER_H

#include <QObject>
#include <QtNetwork/QUdpSocket>

class UdpReceiver : public QObject
{

    Q_OBJECT


public:
    UdpReceiver(QObject *P =0);
    ~UdpReceiver();

public slots:
    void receive();

private:
    QUdpSocket *uSocket;
};

#endif // UDPRECEIVER_H
