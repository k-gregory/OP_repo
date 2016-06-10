#ifndef IINPUTCREATOR
#define IINPUTCREATOR

#include <QWidget>
#include <QString>
#include "inputlistitem.h"

class IInputCreator{
public:
    virtual QString creatorName() const = 0;
    virtual qSynth::InputListItem* createInput(QString&& name,QWidget* parent = nullptr) = 0;
};

#endif // IINPUTCREATOR

