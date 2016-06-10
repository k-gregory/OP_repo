#ifndef QSYNTH_GENERATOR_H
#define QSYNTH_GENERATOR_H

#include "iaudiocallback.h"

namespace qSynth {

class Generator : public IAudioCallback
{
public:
    Generator();
    void processInput(const std::vector<GenericInputAction>& input) override;
    void fillBuffer(float* buffer, unsigned long frames) override;
};

} // namespace qSynth

#endif // QSYNTH_GENERATOR_H
