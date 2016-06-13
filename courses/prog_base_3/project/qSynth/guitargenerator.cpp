#include "guitargenerator.h"

#include <cmath>
#include <algorithm>
#include <QDebug>

namespace qSynth {
namespace guitar {

bool GuitarGenerator::precalculated = false;
using pAmplsArrType = float(*)[GuitarGenerator::harmAmplitudesCount];
using pKeysArrType = float(*)[GuitarGenerator::swing_last_pos];
pAmplsArrType GuitarGenerator::harmAmplitudes =
        new float[GuitarGenerator::swing_last_pos+SAMPLE_RATE]
                 [GuitarGenerator::harmAmplitudesCount];
pKeysArrType GuitarGenerator::precalculatedMidiKeys =
        new float[GuitarGenerator::midiKeysNum][GuitarGenerator::swing_last_pos];

QString GuitarGenerator::name() const{
    return "Guitar";
}

GuitarGenerator::GuitarGenerator(){
    initStrings();
    if(!precalculated){
    precalculateAmplitudes();
    precalculateMidiKeys();
    precalculated = true;
    }
}

GuitarGenerator::~GuitarGenerator(){
}

void GuitarGenerator::initStrings(){
    for(unsigned long i = 0; i < string_count; i++){
        strings[i].active = false;
        strings[i].base_freq = 0;
        strings[i].samples_played = 0;
    }
}

void GuitarGenerator::setStringFrequency(unsigned int string, float freq){
    if(string < 1 || string > string_count){
        qDebug()<<"Too big string number: "<<string;
        return;
    }
    strings[string-1].base_freq = freq;
}

void GuitarGenerator::playString(unsigned int string){
    if(string < 1 || string > string_count){
        qDebug()<<"Too big string number: "<<string;
        return;
    }
    strings[string-1].active = true;
    strings[string-1].samples_played = 0;
}

void GuitarGenerator::playString(unsigned int string, float freq){
    qDebug()<<string<<" plays "<<freq;
    setStringFrequency(string, freq);
    playString(string);
}

void GuitarGenerator::playFree(float freq){
    freeNotes.push_back({freq,0,true});
}

void GuitarGenerator::playFreeMidi(unsigned char k){
    if(k < midiFirstKey || k > midiLastKey) return;
    freeMidiKeys.push_back({0,k});
}

void GuitarGenerator::precalculateAmplitudes(){
    using ulong = unsigned long;
    for(ulong sample = 0; sample < swing_last_pos + SAMPLE_RATE; sample++){
        for(ulong i = 0; i  < harmAmplitudesCount; i++){
            float t = sample * sample_time;
            harmAmplitudes[sample][i] = harmAmplitudesInfo[i].calc(t*SAMPLE_RATE)/6000;
        }
    }
}

static constexpr float freqFromMidiKey(char key){
    constexpr float coef = log(2)/12.f;
    return std::exp((key - 69) * coef)*440;
}

void GuitarGenerator::precalculateMidiKeys(){
    using ulong = unsigned long;
    for(ulong key = midiFirstKey; key < midiLastKey; key++){
        float freq = freqFromMidiKey(key-midiFirstKey);
        StringInfo s = {freq,0,true};
        for(ulong sample = 0; sample < swing_last_pos; sample++){
            precalculatedMidiKeys[key - midiFirstKey][sample] = calcStringSample(s);
        }
    }
}

void GuitarGenerator::process(float *samples_out, unsigned long samplesCount){
    using ulong = unsigned long;
    std::fill(samples_out,samples_out+samplesCount, 0);
    //For each sample
    for(ulong sample = 0; sample < samplesCount; sample++){
        //Sample accumulator
        float curr_sample = 0;

        //For each string
        for(unsigned int i = 0; i < string_count; i++)
            curr_sample+=calcStringSample(strings[i]);
        //For each free note
        for(StringInfo& s : freeNotes)
            curr_sample += calcStringSample(s);

        samples_out[sample] = curr_sample;///4;
    }

    for(auto& p : freeMidiKeys){
        ulong& pos = p.first;
        unsigned char k = p.second;
        ulong last = std::min(samplesCount, swing_last_pos - pos);
        ulong sample;
        for(sample = 0; sample < last; sample++){
            samples_out[sample] += precalculatedMidiKeys[k][pos+sample];
        }
        pos += sample;
    }
    freeMidiKeys.erase(std::remove_if(freeMidiKeys.begin(),freeMidiKeys.end(),[](auto& p){
        return p.first == swing_last_pos;
    }),freeMidiKeys.end());

    //Deactivate finished strings
    for(ulong i = 0; i  <string_count; i++)
        if(strings[i].active && strings[i].samples_played > swing_last_pos)
            strings[i].active = false;
    freeNotes.erase(std::remove_if(freeNotes.begin(),freeNotes.end(),
                                   [](const StringInfo& s){
        return s.samples_played >= swing_last_pos;
    }),freeNotes.end());
}

} // namespace guitar
} // namespace qSynth

