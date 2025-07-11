#include "udpclient.h"
#include <QNetworkDatagram>

#include<unistd.h>

UdpClient::UdpClient(QObject *parent)
    : QObject{parent}
{
    udpSocket = new QUdpSocket(this);
    // 当 udpSocket 有可读数据时，调用 processPendingDatagrams 函数处理
    connect(udpSocket, &QUdpSocket::readyRead, this, &UdpClient::processPendingDatagrams);
}

// sendMessage 函数用于发送 UDP 消息
// 将传入的 message 转为字节数组，然后通过 udpSocket 发送到指定的主机和端口
void UdpClient::sendMessage(const QString &message, const QString &host, quint16 port) {
    QByteArray data = message.toUtf8(); // 将 QString 转为字节数组
    udpSocket->writeDatagram(data, QHostAddress(host), port); // 发送数据包
}

// bindSocket 函数用于绑定 UDP 套接字到某个端口，允许接收数据
void UdpClient::bindSocket(quint16 port) {
    udpSocket->bind(QHostAddress::Any, port); // 绑定到指定端口，监听所有网络接口
}

// processPendingDatagrams 函数处理接收到的 UDP 数据包
void UdpClient::processPendingDatagrams() {
    //QString cmd("/root/digital");
    // 检查是否有待接收的数据包
    while (udpSocket->hasPendingDatagrams()) {
        // 获取并处理每一个数据包
        QNetworkDatagram datagram = udpSocket->receiveDatagram();
        QByteArray data = datagram.data();
        // 发出 messageReceived 信号，将接收到的消息发送给 QML
        switch(data[0]){
        case 'l':
            emit msgLogin(&data[1]);
            break;
        case 'r':
            emit msgRegister(&data[1]);
            break;
        case 'd':
            emit msgDelivery(&data[1]);
            if(fork() == 0)
                execlp("/root/digital", "/root/digital", &data[1], NULL);
            //cmd = cmd+' '+&data[1];
            //system(cmd.toStdString().c_str());
            break;
        case 'p':
            emit msgPickup(&data[1]);
            if(fork() == 0)
                execlp("/root/digital", "/root/digital", &data[1], NULL);
            break;
        default:
            emit messageReceived(QString(datagram.data()));
        }
        emit messageReceived(QString(datagram.data()));
    }
}
