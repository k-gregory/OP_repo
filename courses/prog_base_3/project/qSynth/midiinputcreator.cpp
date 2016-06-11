#include "midiinputcreator.h"
#include <QFileDialog>
#include "lib/midifile/MidiFile.h"
#include "midiinput.h"

MidiInputCreator::MidiInputCreator(qSynth::Generator* generator)
    : g(generator)
{

}

QString MidiInputCreator::creatorName() const{
    return "Midi";
}

qSynth::InputListItem* MidiInputCreator::createInput(QString &&name, QWidget *parent){
    QString file = QFileDialog::getOpenFileName(parent);
    if(file.isNull()) return nullptr;

    MidiInput* m = new MidiInput(file,g);

    return new qSynth::InputListItem(std::move(name),m,parent,nullptr);
}



