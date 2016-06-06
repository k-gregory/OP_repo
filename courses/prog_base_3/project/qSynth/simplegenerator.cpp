#include "simplegenerator.h"

#include <algorithm>
#include <cmath>

namespace qSynth {

static constexpr unsigned int sample_rate=44000;
static constexpr unsigned int string_time = 5;
static constexpr unsigned long end_p = sample_rate * string_time;
static constexpr float k = -10.f/end_p;

SimpleGenerator::SimpleGenerator()
{
}

void SimpleGenerator::processInput(const std::vector<GenericInputAction> &input){
    input_lock.lock();
    danger_buffer.insert(danger_buffer.end(),input.begin(), input.end());
    input_lock.unlock();
}

static float adsr(unsigned int pos){
    return exp(k*pos);
}

void SimpleGenerator::dangerProcessInput(){
    for(GenericInputAction& a : danger_buffer){
        if(a.type!=GenericInputAction::KeyPress) continue;
        int nw = a.key - '1';
        if(nw < 0 || nw > 9) continue;
        waves.push_back({120+nw*30,0});
    }
    danger_buffer.clear();
}

void SimpleGenerator::fillBuffer(float *buffer, unsigned long frames){
    if(input_lock.try_lock()){
        dangerProcessInput();
        input_lock.unlock();
    }

    float ncoef = 1.f/std::sqrt(waves.size()+1);
    std::fill(buffer,buffer+frames, 0.f);
    for(Wave& w : waves){
        unsigned long last = w.played_time + frames;
        float* buff = buffer;
        for(; w.played_time < last; w.played_time++){
            float t = w.played_time * 1.f/ sample_rate;
            *buff++ += std::sin(t*2*3.14*w.frequency+std::sin(t))*adsr(w.played_time);
        }
    }

    waves.erase(std::remove_if(waves.begin(),
                               waves.end(),
                               [](const Wave& w){
                    return w.played_time > end_p;
                }),waves.end());

    for(unsigned int i =0; i < frames; i++){
         buffer[i]*=ncoef;
    }
}

} // namespace qSynth

