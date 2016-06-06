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
}

void SimpleGenerator::processInput(const std::vector<GenericInputAction> &input){
    input_lock.lock();
    danger_buffer.insert(danger_buffer.end(),input.begin(), input.end());
    input_lock.unlock();
}

/*static float adsr(unsigned int pos){
    return exp(k*pos);
}*/


#define LEN(arr) (sizeof(arr)/sizeof((arr)[0]))

struct arr2{
    int a;
    int b;
};

static arr2 keyPos(int key){
    constexpr int first_row[] = {'q','w','e','r','t','y','u','i','o','p'};
    constexpr int second_row[] = {'a','s','d','f','g','h','j','k','l'};
    constexpr int third_row[] = {'z','x','c','v','b','n','m'};
    for(unsigned int i = 0; i < LEN(first_row); i++){
        if(first_row[i] == key) return {1,i};
    }
    for(unsigned int i = 0; i < LEN(second_row); i++){
        if(second_row[i] == key) return {2,i};
    }
    for(unsigned int i = 0; i < LEN(third_row); i++){
        if(third_row[i] == key) return {3,i};
    }
    return {-1,-1};
}

void SimpleGenerator::dangerProcessInput(){
    for(GenericInputAction& a : danger_buffer){
        if(a.type!=GenericInputAction::KeyPress) continue;
        if(a.key < 10 || a.key > 100) continue;
        //waves.push_back({100+(a.key-'1')*30,0});
        arr2 a2 = keyPos(a.specialInfo[1]);
        qDebug()<<a2.a<<a2.b;
        if(a2.a!=-1){
            qDebug()<<"N";
            guitar_gen.playString(a2.a,(a2.b+1)*50);
        }
    }
    danger_buffer.clear();
}

void SimpleGenerator::fillBuffer(float *buffer, unsigned long frames){
    if(input_lock.try_lock()){
        dangerProcessInput();
        input_lock.unlock();
    }

    /*
    std::fill(buffer,buffer+frames, 0.f);
    for(Wave& w : waves){
        using std::sin;
        unsigned long last = w.played_time + frames;
        float* buff = buffer;
        for(; w.played_time < last; w.played_time++){
            float t = w.played_time * 1.f/ sample_rate;
            float arg = 2*3.14*t*w.frequency;
            *buff++ += sin(arg*2)*sin(arg)*sin(arg)*adsr(w.played_time);
        }
    }

    waves.erase(std::remove_if(waves.begin(),
                               waves.end(),
                               [](const Wave& w){
                    return w.played_time > end_p;
                }),waves.end());

    for(unsigned int i =0; i < frames; i++){
        buffer[i] = std::atan(buffer[i]);
    }
    */
    guitar_gen.process(buffer,buffer, frames);
}

} // namespace qSynth

