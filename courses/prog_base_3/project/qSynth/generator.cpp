#include "generator.h"
#include <algorithm>
#include <QDebug>

using namespace std;

namespace qSynth {

Generator::Generator(IAudioEffect* effect,QObject* parent) : QObject(parent), effect(effect)
{
}

void Generator::addInputProcessor(IInputProcessor *p){
    input_processors.push_back(p);
}

void Generator::setEffect(IAudioEffect *value)
{
    effect = value;
}

void Generator::processInput(const std::vector<GenericInputAction> &input){
    input_lock.lock();
    danger_buffer.insert(danger_buffer.end(),input.begin(), input.end());
    input_lock.unlock();
}

void Generator::dangerProcessInput(){
    for(IInputProcessor* p : input_processors){
        p->process(danger_buffer);
    }
    danger_buffer.clear();
}

void Generator::fillBuffer(float *buffer, unsigned long frames){    
    if(input_lock.try_lock()){
        dangerProcessInput();
        input_lock.unlock();
    }
    effect->process(buffer,frames);
    emit framesGenerated(frames);
}

} // namespace qSynth

