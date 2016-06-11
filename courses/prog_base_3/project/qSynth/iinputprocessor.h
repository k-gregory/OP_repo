#ifndef IINPUTPROCESSOR_H
#define IINPUTPROCESSOR_H

#include "genericinputaction.h"
#include <vector>

class IInputProcessor
{
public:
    virtual void process(std::vector<qSynth::GenericInputAction> input) = 0;
};

#endif // IINPUTPROCESSOR_H
