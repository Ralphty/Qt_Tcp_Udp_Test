#include <QtCore/QCoreApplication>
#include "udpreceiver.h"
#include <iostream>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    UdpReceiver udprev;
    std::cout<<"---Receiver---"<<std::endl;
    
    return a.exec();
}
