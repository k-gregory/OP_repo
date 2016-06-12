#ifndef KEYREADINPUTCREATOR_H
#define KEYREADINPUTCREATOR_H

#include "iinputcreator.h"
#include "keyboardreaderwidget.h"

class KeyReadInputCreator : public IInputCreator
{
public:
    KeyReadInputCreator(qSynth::KeyboardReaderWidget* p);
    QString creatorName() const override;
    qSynth::InputListItem* createInput(QString &&name, QWidget *parent) override;
private:
    qSynth::KeyboardReaderWidget* w;
};

#endif // KEYREADINPUTCREATOR_H
