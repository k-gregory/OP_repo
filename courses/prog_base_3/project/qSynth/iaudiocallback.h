#ifndef IAUDIOCALLBACK
#define IAUDIOCALLBACK

#include "igenericinput.h"

namespace qSynth{

class IAudioCallback{
public:
    virtual void processInput(const std::vector<GenericInputAction>& input) = 0;
    virtual void fillBuffer(float* buffer, unsigned long frames) = 0;
};

}

#endif // IAUDIOCALLBACK

