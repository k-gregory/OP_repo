#ifndef IAUDIOBACKEND
#define IAUDIOBACKEND

#include "constants.h"

namespace qSynth {

class IAudioBackend{
public:
    virtual void start() = 0;
    virtual void pause() = 0;
    virtual void unpause() = 0;
    virtual void stop() = 0;
};

}

#endif // IAUDIOBACKEND

