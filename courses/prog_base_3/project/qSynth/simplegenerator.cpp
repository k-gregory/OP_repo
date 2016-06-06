#include "simplegenerator.h"

#include <algorithm>
#include <cmath>
#include <QDebug>

namespace qSynth {

static constexpr unsigned int sample_rate=44000;
static constexpr unsigned int string_time = 10;
static constexpr unsigned long end_p = sample_rate * string_time;
static constexpr float k = -7.f/end_p;

SimpleGenerator::SimpleGenerator()
{
    waves.push_back({250,0});
}

static float adsr(unsigned int pos){
    return exp(k*pos);
}

void SimpleGenerator::fillBuffer(float *buffer, unsigned long frames){
    float ncoef = 1.f/(waves.size()+1);
    std::fill(buffer,buffer+frames, 0.f);
    for(Wave& w : waves){
        unsigned long last = w.played_time + frames;
        float* buff = buffer;
        for(; w.played_time < last; w.played_time++){
            float t = w.played_time * 1.f/ sample_rate;
            *buff++ = std::sin(t*2*3.14*w.frequency)*adsr(w.played_time);
        }
    }
   for(int i =0; i < frames; i++){
        buffer[i]*=ncoef;
   }
}

} // namespace qSynth

