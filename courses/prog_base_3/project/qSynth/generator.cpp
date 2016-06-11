#include "generator.h"
#include <algorithm>

using namespace std;

namespace qSynth {

Generator::Generator(QObject* parent) : QObject(parent)
{

}

void Generator::processInput(const std::vector<GenericInputAction> &input){
    input_lock.lock();
    danger_buffer.insert(danger_buffer.end(),input.begin(), input.end());
    input_lock.unlock();
}

void Generator::dangerProcessInput(){

}

void Generator::fillBuffer(float *buffer, unsigned long frames){
    fill(buffer, buffer+frames, 0.f);
    emit framesGenerated(frames);
}

} // namespace qSynth

