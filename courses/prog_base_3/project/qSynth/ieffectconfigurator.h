#ifndef QSYNTH_IEFFECTCONFIGURATOR_H
#define QSYNTH_IEFFECTCONFIGURATOR_H

#include "iaudioeffect.h"

namespace qSynth {

class IEffectConfigurator
{
public:
    virtual IAudioEffect* createNew() = 0;
    virtual bool configure(IAudioEffect* effect) = 0;
};

} // namespace qSynth

#endif // QSYNTH_IEFFECTCONFIGURATOR_H
