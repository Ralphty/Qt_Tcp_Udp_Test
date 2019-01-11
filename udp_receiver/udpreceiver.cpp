#include "udpreceiver.h"
#include <QByteArray>
#include <iostream>
#include <QDebug>

const quint16 PORT = 2333;

UdpReceiver::UdpReceiver(QObject *p) :
    QObject(p)
{
    uSocket = new QUdpSocket;
    uSocket->bind(QHostAddress("192.168.1.103"),PORT);
    connect(uSocket,SIGNAL(readyRead()),this,SLOT(receive()));
}

UdpReceiver::~UdpReceiver()
{
    delete uSocket;
}

void UdpReceiver::receive()
{
    QByteArray ba;
    while(uSocket->hasPendingDatagrams())
    {
        ba.resize(uSocket->pendingDatagramSize());
        uSocket->readDatagram(ba.data(),ba.size());
        //std::cout<<ba.data()<<std::endl;
        qDebug()<<ba.data();
    }
}
