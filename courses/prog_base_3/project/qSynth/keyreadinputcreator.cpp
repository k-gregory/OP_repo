#include "keyreadinputcreator.h"

KeyReadInputCreator::KeyReadInputCreator(qSynth::KeyboardReaderWidget* w)
    : w(w)
{

}

QString KeyReadInputCreator::creatorName() const{
    return "KeyRead widget";
}

qSynth::InputListItem* KeyReadInputCreator::createInput(QString &&name, QWidget *parent){
    return new qSynth::InputListItem(std::move(name),w,parent);
}

