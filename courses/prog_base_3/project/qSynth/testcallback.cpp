#include "testcallback.h"

#include <cmath>

namespace qSynth {

TestCallback::TestCallback()
{

}

void TestCallback::processInput(const std::vector<GenericInputAction> &){

}

void TestCallback::fillBuffer(float *buffer, unsigned long frames){
    unsigned long last = pos + frames;
    for(; pos < last; pos++){
        using std::sin;
        float c = 2 * 3.14/SAMPLE_RATE;
        float cp = c * pos;
        *buffer++ = sin(cp*300);
    }
}

} // namespace qSynth

