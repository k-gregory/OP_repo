#ifndef QSYNTH_IGENERICINPUT_H
#define QSYNTH_IGENERICINPUT_H

#include "genericinputaction.h"
#include <vector>

namespace qSynth {

class IGenericInput
{
public:
    virtual std::vector<GenericInputAction> pollInput() = 0;
    virtual bool hasInput() = 0;
};

} // namespace qSynth

#endif // QSYNTH_IGENERICINPUT_H
