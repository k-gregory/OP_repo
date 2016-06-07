#include "guitargenerator.h"

#include <cmath>
#include <algorithm>
#include <QDebug>

namespace qSynth {
namespace guitar {

GuitarGenerator::GuitarGenerator(){
    initStrings();
    precalculateAmplitudes();
}

GuitarGenerator::~GuitarGenerator(){
    delete[] harmAmplitudes;
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

void GuitarGenerator::precalculateAmplitudes(){
    using ulong = unsigned long;
    for(ulong sample = 0; sample < swing_last_pos; sample++){
        for(ulong i = 0; i  < harmAmplitudesCount; i++){
            float t = sample * sample_time;
            harmAmplitudes[sample][i] = harmAmplitudesInfo[i].calc(t*SAMPLE_RATE)/6000;
        }
    }
}

void GuitarGenerator::process(const float *, float *samples_out, unsigned long samplesCount){
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

