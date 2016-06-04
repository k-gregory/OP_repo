#include "testcallback.h"

#include <cmath>

namespace qSynth {

TestCallback::TestCallback()
{

}

void TestCallback::fillBuffer(float *buffer, unsigned long frames){
    unsigned long last = pos + frames;
    for(; pos < last; pos++){
        using std::sin;
        float c = freq * 2 * 3.14/SAMPLE_RATE;
        float cp = c * pos;
        *buffer++ = sin(10*cp*sin(cp/5000));
    }
}

} // namespace qSynth

