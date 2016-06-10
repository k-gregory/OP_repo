#include "simplegenerator.h"

#include <algorithm>
#include <cmath>
#include <QDebug>

namespace qSynth {

static constexpr unsigned int sample_rate=44000;
static constexpr unsigned int string_time = 2;
static constexpr unsigned long end_p = sample_rate * string_time;
static constexpr float k = -10.f/end_p;

SimpleGenerator::SimpleGenerator()
{
    guitar_gen.playString(1,196.0);
}

void SimpleGenerator::processInput(const std::vector<GenericInputAction> &input){
    input_lock.lock();
    danger_buffer.insert(danger_buffer.end(),input.begin(), input.end());
    input_lock.unlock();
}

#define LEN(arr) (sizeof(arr)/sizeof((arr)[0]))

struct arr3{
    int a;
    int b;
    int c;
};

static arr3 keyPos(int key){
    constexpr int first_row[] = {'q','w','e','r','t','y','u','i','o','p'};
    constexpr int second_row[] = {'a','s','d','f','g','h','j','k','l'};
    constexpr int third_row[] = {'z','x','c','v','b','n','m'};
    for(unsigned int i = 0; i < LEN(first_row); i++){
        if(first_row[i] == key) return {1,(int)i+1,(int)i+1};
    }
    for(unsigned int i = 0; i < LEN(second_row); i++){
        if(second_row[i] == key) return {2,(int)i+1,(int)LEN(first_row)+(int)i+1};
    }
    for(unsigned int i = 0; i < LEN(third_row); i++){
        if(third_row[i] == key) return {3,(int)i+1,(int)(LEN(first_row)+LEN(second_row)+1+(int)i)};
    }
    return {-1,-1,-1};
}

void SimpleGenerator::dangerProcessInput(){
    for(GenericInputAction& a : danger_buffer){
        if(a.type!=GenericInputAction::KeyPress) continue;
        if(a.key < 10 || a.key > 100) continue;
        //guitar_gen.playFree(440.0);
        //waves.push_back({100+(a.key-'1')*30,0});
        arr3 a2 = keyPos(a.specialInfo[1]);
        if(a2.a!=-1){
            guitar_gen.playString(a2.a,(a2.b+1)*50);
            // guitar_gen.playFree(a2.c*20);
        }
    }
    danger_buffer.clear();
}

inline static float hardClip(float val, float s){
    if(val > s)
        val = s;
    else if(val < -s)
        val = -s;
    return val/s;
}

inline static float softClip(float val, float s){
    return std::atan(val*s)/1.57f;
}

void SimpleGenerator::fillBuffer(float *buffer, unsigned long frames){
    if(input_lock.try_lock()){
        dangerProcessInput();
        input_lock.unlock();
    }
    guitar_gen.process(buffer,buffer, frames);

    for(unsigned long i = 0; i < frames; i++){
        buffer[i] = hardClip(buffer[i],0.05);
    }
}

} // namespace qSynth

