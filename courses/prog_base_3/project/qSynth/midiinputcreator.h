#ifndef MIDIINPUTCREATOR_H
#define MIDIINPUTCREATOR_H

#include "iinputcreator.h"
#include "generator.h"

class MidiInputCreator : public IInputCreator
{
public:
    MidiInputCreator(qSynth::Generator* g);
    QString creatorName() const override;
    qSynth::InputListItem* createInput(QString &&name, QWidget *parent) override;
private:
    qSynth::Generator* g;
};

#endif // MIDIINPUTCREATOR_H
