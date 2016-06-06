#ifndef QSYNTH_TESTCALLBACK_H
#define QSYNTH_TESTCALLBACK_H

#include "iaudiocallback.h"
#include "constants.h"

namespace qSynth {

class TestCallback : public IAudioCallback
{
    unsigned long pos = 0;
    float freq = 240;
public:
    TestCallback();
    void processInput(const std::vector<GenericInputAction>&) override;
    void fillBuffer(float* buffer, unsigned long frames) override;
};

} // namespace qSynth

#endif // QSYNTH_TESTCALLBACK_H
