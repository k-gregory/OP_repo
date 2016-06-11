#include "noopeffect.h"

namespace qSynth {

NOOPEffect::NOOPEffect()
{

}

void NOOPEffect::process(float *, unsigned long){
    return;
}

QString NOOPEffect::name() const{
    return "NOOP";
}

} // namespace qSynth

