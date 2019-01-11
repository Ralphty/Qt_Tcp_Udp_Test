#include <QtCore/QCoreApplication>
#include <QByteArray>
#include <QtNetwork/QUdpSocket>
#include <iostream>
#include <QDebug>
#include <QTimer>

const quint16 PORT = 2333;



int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QUdpSocket qus;
    QString msg = "Hello World";
    for(int i=0;i<100;i++)
    {
        qus.writeDatagram(msg.toLatin1(),msg.length(),QHostAddress("192.168.1.102"),PORT);
    }
    qDebug()<<"---Sender---";
    //std::cout<<"---Sender---"<<std::endl;
    return a.exec();
}
