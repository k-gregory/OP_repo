#include "midiinput.h"
#include <QDebug>

MidiInput::MidiInput(QString filename,qSynth::Generator* g,QObject* p, float ticks)
    : QObject(p), tickCoef(ticks/SAMPLE_RATE)
{
    f.read(filename.toStdString());
    for(int i = 0; i < f.size(); i++)
        to_play.push_back({0,f[i]});
    connect(g,&qSynth::Generator::framesGenerated,this,[this](unsigned long playedFrames){
        this->realTick += playedFrames * tickCoef;
    });
}

std::vector<qSynth::GenericInputAction> MidiInput::pollInput(){
    std::vector<qSynth::GenericInputAction> result;
    for(auto& x : to_play){
        int& currentTrackPos = x.first;
        MidiEventList& track = x.second;
        while(currentTrackPos < track.size()
              && track[currentTrackPos].tick <= realTick){
            MidiEvent& ev = track[currentTrackPos];
            if(ev.isNoteOn()){
                qSynth::GenericInputAction act;
                act.type = qSynth::GenericInputAction::KeyPress;
                act.key = ev[1]+21;
                result.push_back(act);
            }
            currentTrackPos++;
        }
    }
    return result;
}

bool MidiInput::hasInput(){
    for(auto& x : to_play){
        if(x.first < realTick)
            return true;
    }
    return false;
}

void MidiInput::setTicksPerSecond(float value)
{
    tickCoef = value/SAMPLE_RATE;
}
