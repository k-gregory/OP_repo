#include "inputlistitem.h"
#include <QMessageBox>

namespace qSynth {

InputListItem::InputListItem(QString &&name, IGenericInput *input, QWidget* parent, QDialog *modificationDialog)
    : name(name), input(input), modificationDialog(modificationDialog), parent(parent)
{

}

const QString& InputListItem::getName() const{
    return name;
}

IGenericInput* InputListItem::getInput() const{
    return input;
}

void InputListItem::modify(){
    if(modificationDialog!=nullptr)
        modificationDialog->exec();
    else {
        QMessageBox mbox(parent);
        mbox.setText("No input modifications available");
        mbox.exec();
    }
}

} // namespace qSynth

