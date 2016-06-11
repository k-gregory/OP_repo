#ifndef MIDIINPUT_H
#define MIDIINPUT_H

#include "constants.h"
#include <QObject>
#include "igenericinput.h"
#include "generator.h"
#include "lib/midifile/MidiFile.h"
#include <vector>

class MidiInput : public QObject, public qSynth::IGenericInput
{
    Q_OBJECT
public:
    explicit MidiInput(QString filename,qSynth::Generator* g, QObject* p = nullptr,float ticks = 2000);
    virtual std::vector<qSynth::GenericInputAction> pollInput() override;
    virtual bool hasInput();
    void setTicksPerSecond(float value);

private:
    float tickCoef;
    std::vector<std::pair<int, MidiEventList>> to_play;
    long realTick = 0;
    MidiFile f;
};

#endif // MIDIINPUT_H
