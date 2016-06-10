#include "udpinputcreator.h"
#include "ui_udpinputcreator.h"
#include "udpinput.h"

QString UDPInputCreator::creatorName() const{
    return "UDP Input";
}

qSynth::InputListItem* UDPInputCreator::createInput(QString&& newName,QWidget *parent){
    if(exec() == Accepted){
     qSynth::UDPInput* inp = new qSynth::UDPInput(parent);
     if(!inp->open(ui->portBox->value())) return nullptr;
     else {
         qSynth::InputListItem* it = new qSynth::InputListItem(std::move(newName),inp,parent,nullptr);
         return it;
     }
    } else {
        return nullptr;
    }
}


UDPInputCreator::UDPInputCreator(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UDPInputCreator)
{
    ui->setupUi(this);
}

UDPInputCreator::~UDPInputCreator()
{
    delete ui;
}
