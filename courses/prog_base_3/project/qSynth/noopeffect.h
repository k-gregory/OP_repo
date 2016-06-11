#ifndef QSYNTH_NOOPEFFECT_H
#define QSYNTH_NOOPEFFECT_H

#include "iaudioeffect.h"

namespace qSynth {

class NOOPEffect : public IAudioEffect
{
public:
    NOOPEffect();
    void process(float *samples, unsigned long samplesCount) override;
    QString name() const override;
};

} // namespace qSynth

#endif // QSYNTH_NOOPEFFECT_H
