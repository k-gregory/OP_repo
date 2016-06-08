#include "udpinput.h"
#include <QDataStream>

namespace qSynth {

UDPInput::UDPInput(QObject* pobj) : QObject(pobj)
{
    sock = new QUdpSocket(pobj);
    connect(sock,&QUdpSocket::readyRead,this,&UDPInput::readDatagrams);
}

bool UDPInput::open(int port){
    return sock->bind(QHostAddress::AnyIPv4,port);
}

void UDPInput::close(){
    sock->close();
}

quint16 UDPInput::getPort(){
    return sock->localPort();
}

UDPInput::~UDPInput(){
    delete sock;
}

void UDPInput::readDatagrams(){
    while(sock->hasPendingDatagrams()){
        int datagramSize;
        QByteArray datagram;
        datagramSize = sock->pendingDatagramSize();
        datagram.resize(datagramSize);
        qDebug()<<datagramSize;
        sock->readDatagram(datagram.data(),datagramSize);
        if(datagramSize != sizeof(qint32)*12) continue;

        qint32 msg[12];
        qint32* recv = (qint32*) datagram.data();
        for(int i = 0; i < 12; i++){
            msg[i] = recv[i];
        }
        GenericInputAction action;
        qint32 t;
        t = msg[0];
        if(t == GenericInputAction::KeyPress)
            action.type = GenericInputAction::KeyPress;
        else if(t==GenericInputAction::KeyRelease)
            action.type = GenericInputAction::KeyRelease;
        else if(t==GenericInputAction::SpecialAction)
            action.type = GenericInputAction::SpecialAction;
        t = msg[1];
        action.key = t;
        for(int i = 0; i < 10; i++){
            t = msg[i+2];
            action.specialInfo[i] = t;
        }

        input_queue.push_back(action);
    }
}

std::vector<GenericInputAction> UDPInput::pollInput(){
    std::vector<GenericInputAction> ret = std::vector<GenericInputAction>(input_queue);
    input_queue.clear();
    return ret;
}

bool UDPInput::hasInput(){
    return input_queue.size()!= 0;
}

} // namespace qSynth

