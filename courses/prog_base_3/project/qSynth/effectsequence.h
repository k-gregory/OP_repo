#ifndef QSYNTH_EFFECTSEQUENCE_H
#define QSYNTH_EFFECTSEQUENCE_H

#include "iaudioeffect.h"
#include "ieffectconfigurator.h"
#include <vector>

namespace qSynth {

class EffectSequence : public IAudioEffect
{
public:
    EffectSequence();
    QString name() const override;
    void process(float* samples, unsigned long frames) override;
    void removeEffect(unsigned int index);
    void insertEffect(unsigned int index, IAudioEffect *effect);
    std::vector<IAudioEffect*> effects;
};

class EffectSequenceConfigurator : public IEffectConfigurator{
public:
    IAudioEffect* createNew() override {
        return new EffectSequence();
    }

    bool configure(IAudioEffect *) override{
        return false;
    }
};

} // namespace qSynth

#endif // QSYNTH_EFFECTSEQUENCE_H
