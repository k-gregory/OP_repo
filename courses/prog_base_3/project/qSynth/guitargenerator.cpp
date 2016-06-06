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
        for(ulong string = 0; string < string_count; string++){
            if(!strings[string].active) continue;
            unsigned long nSample = strings[string].samples_played++;
            float t = nSample * sample_time;
            //For each harmonic of string
            for(ulong harmIndex = 0; harmIndex < harmAmplitudesCount; harmIndex++){
                float freq = strings[string].base_freq*(1+harmIndex);
                if(harmIndex == 0) freq+=2;
                curr_sample+=std::sin(2*PI*t*freq)*harmAmplitudes[nSample][harmIndex];
            }
            /*curr_sample+=inharmAmplitudesInfo.strength*
                    std::sin(2*PI*t*strings[string].base_freq+inharmAmplitudesInfo.freqShift)*
                    inharmAmplitudesInfo.amplitude.calc(t)/6000;*/
        }
        samples_out[sample] = curr_sample;
    }
    //Deactivate finished strings
    for(ulong i = 0; i  <string_count; i++)
        if(strings[i].active && strings[i].samples_played > swing_last_pos)
            strings[i].active = false;
}

} // namespace guitar
} // namespace qSynth

