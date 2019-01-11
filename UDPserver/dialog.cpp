#include "dialog.h"
#include "ui_dialog.h"
#include <QDebug>

#include <QHostAddress>

static int countTransfer=0;
static int countReceiver=0;

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    this->setWindowTitle("UDP Server");
    this->timer = new QTimer();

    this->isStarted = false;
    this->port = 45454;

    this->udpSocketTransfer = new QUdpSocket;
    this->udpSocketReceive = new QUdpSocket;

    this->udpSocketReceive->bind(QHostAddress("192.168.1.103"),port);
    connect(this->udpSocketReceive,SIGNAL(readyRead()),this,SLOT(processPendingDatagram()));


    connect(this->timer,SIGNAL(timeout()),this,SLOT(TimeOut()));
    connect(this->ui->StartBtn,SIGNAL(clicked()),this,SLOT(StartBtnClicked()));
}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::StartBtnClicked()
{
    if(!this->isStarted)
    {
        this->isStarted = true;
        this->ui->StartBtn->setText(tr("stop"));
        this->timer->start(40);
    }
    else
    {
        this->isStarted = false;
        this->ui->StartBtn->setText(tr("start"));
        this->timer->stop();
        qDebug()<<"countTransfer="<<countTransfer;
    }
}

void Dialog::TimeOut()
{
    #define dataNumber 320*3
    #define dataNumber3 320 *9
    int sampledData[dataNumber][8]={};
    char transferdata[dataNumber3]= {0};
    int temp=0;
    //initial data array
    for(int j =0;j<dataNumber;j++)
    {
        for(int k  =0;k<8;k++)
        {
            sampledData[j][k] = 0xffff;
        }
    }


   //add dada
    for(int j =0;j<dataNumber;j++)
    {
        temp = 0;
        for(int k  =0;k<8;k++)
        {
           temp += sampledData[j][k]>>3;
        }

        transferdata[j*3] = (temp & 0xff);
        transferdata[j*3+1] = (temp & 0xff00)>>8;
        transferdata[j*3+2] = (temp & 0xff0000)>>16;
    }
    //this->udpSocketTransfer->writeDatagram(transferdata,dataNumber3,QHostAddress("192.168.1.102"),port);
    //this->udpSocketTransfer->writeDatagram(transferdata,dataNumber3,QHostAddress("192.168.1.22"),port);
    QHostAddress mcast_addr("224.0.0.17");
    this->udpSocketTransfer->writeDatagram(transferdata,dataNumber3,mcast_addr,port);
    //this->udpSocketTransfer->writeDatagram(transferdata,mcast_addr,port);
    countTransfer++;
}

void Dialog::processPendingDatagram()
{
    while(this->udpSocketReceive->hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(this->udpSocketReceive->pendingDatagramSize());
        countReceiver +=this->udpSocketReceive->readDatagram(datagram.data(),datagram.size());
        qDebug()<<datagram.size();
        qDebug()<<countReceiver;
    }
}













