#include "udpinput.h"
#include <QDataStream>

namespace qSynth {

UDPInput::UDPInput(QObject* pobj) : QObject(pobj)
{
    sock = new QUdpSocket();
    connect(sock,&QUdpSocket::readyRead,this,&UDPInput::readDatagrams);
    sock->bind(QHostAddress::AnyIPv4,8000);
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
        //qDebug()<<"First symbol";
        //qDebug()<<datagram[0];
        sock->readDatagram(datagram.data(),datagramSize);
        if(datagramSize != sizeof(qint32)*12) continue;

        QDataStream data(datagram);
        GenericInputAction action;
        qint32 t;
        data >> t;
        if(t == GenericInputAction::KeyPress)
            action.type = GenericInputAction::KeyPress;
        else if(t==GenericInputAction::KeyRelease)
            action.type = GenericInputAction::KeyRelease;
        else if(t==GenericInputAction::SpecialAction)
            action.type = GenericInputAction::SpecialAction;
        data >> t;
        action.key = t;
        for(int i = 0; i < 10; i++){
            data >> t;
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
    return input_queue.size() != 0;
}

} // namespace qSynth

