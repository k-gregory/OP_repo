#ifndef QSYNTH_SIMPLEGENERATOR_H
#define QSYNTH_SIMPLEGENERATOR_H

#include "iaudiocallback.h"
#include <vector>

namespace qSynth {

struct Wave {
    int frequency;
    unsigned long played_time;
};

class SimpleGenerator : public IAudioCallback
{
public:
    SimpleGenerator();
    void fillBuffer(float* buffer, unsigned long frames);
private:
    std::vector<Wave> waves;
};

} // namespace qSynth

#endif // QSYNTH_SIMPLEGENERATOR_H
