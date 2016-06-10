#ifndef UDPINPUTCREATOR_H
#define UDPINPUTCREATOR_H

#include "iinputcreator.h"
#include <QDialog>

namespace Ui {
class UDPInputCreator;
}

class UDPInputCreator : public QDialog, public IInputCreator
{
    Q_OBJECT

public:
    explicit UDPInputCreator(QWidget *parent = 0);
    ~UDPInputCreator();
    QString creatorName() const override;
    qSynth::InputListItem* createInput(QString&& newName,QWidget *parent) override;

private:
    Ui::UDPInputCreator *ui;
};

#endif // UDPINPUTCREATOR_H
