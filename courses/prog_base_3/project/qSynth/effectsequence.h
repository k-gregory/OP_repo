#ifndef QSYNTH_EFFECTSEQUENCE_H
#define QSYNTH_EFFECTSEQUENCE_H

#include "iaudioeffect.h"
#include <vector>

namespace qSynth {

class EffectSequence : public IAudioEffect
{
public:
    EffectSequence();
    void process(float* samples, unsigned long frames) override;
    void removeEffect(unsigned int index);
    void insertEffect(unsigned int index, IAudioEffect *effect);
    std::vector<IAudioEffect*> effects;
};

} // namespace qSynth

#endif // QSYNTH_EFFECTSEQUENCE_H
