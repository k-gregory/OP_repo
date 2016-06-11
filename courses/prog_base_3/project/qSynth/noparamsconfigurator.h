#ifndef QSYNTH_NOPARAMSCONFIGURATOR_H
#define QSYNTH_NOPARAMSCONFIGURATOR_H

#include "ieffectconfigurator.h"

namespace qSynth {

template<typename T>
class NoParamsConfigurator : IEffectConfigurator
{
public:
    IAudioEffect* createNew(){
        return new T;
    }
    bool configure(IAudioEffect *effect){
        return true;
    }
};

} // namespace qSynth

#endif // QSYNTH_NOPARAMSCONFIGURATOR_H
