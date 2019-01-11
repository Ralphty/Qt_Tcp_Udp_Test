#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QtNetwork/QUdpSocket>
#include <QTimer>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

public slots:
    void StartBtnClicked();
    void TimeOut();
    void processPendingDatagram();

private:
    Ui::Dialog *ui;
    int port;
    bool isStarted;
    QUdpSocket *udpSocketTransfer;
    QUdpSocket *udpSocketReceive;
    QTimer *timer;
};

#endif // DIALOG_H
