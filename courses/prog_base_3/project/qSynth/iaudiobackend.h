#ifndef IAUDIOBACKEND
#define IAUDIOBACKEND

#include "constants.h"

namespace qSynth {

class IAudioBackend{
public:
    virtual void start() = 0;
    virtual void stop() = 0;
    virtual void togglePause() = 0;
};

}

#endif // IAUDIOBACKEND

