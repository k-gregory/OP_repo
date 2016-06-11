#include "effectsequence.h"

namespace qSynth {

QString EffectSequence::name() const{
    return "Sequence";
}

EffectSequence::EffectSequence()
{

}

void EffectSequence::process(float *samples, unsigned long frames){
    for(auto& f : effects)
        f->process(samples,frames);
}

void EffectSequence::removeEffect(unsigned int index){
    if(index >= effects.size()) return;
    effects.erase(effects.begin() + index);
}

void EffectSequence::insertEffect(unsigned int index, IAudioEffect *effect){
    if(index >= effects.size()) return;
    effects.insert(effects.begin() + index, effect);
}

} // namespace qSynth

