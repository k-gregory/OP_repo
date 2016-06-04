#ifndef PABACKEND_H
#define PABACKEND_H

#include "iaudiobackend.h"
#include "iaudiocallback.h"

#include <portaudio.h>

#define PA_BACKEND_BUFFER (512)

namespace qSynth{

class PABackend : public IAudioBackend
{
public:
    PABackend(IAudioCallback* callback);
    ~PABackend();
    void start() override;
    void stop() override;
    void pause() override;
    void unpause() override;
private:
    PaStream* stream;
    IAudioCallback* cb;
    static int callback(const void* in, void* out, unsigned long frames,
                         const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags flags,
                         void* userdata);
};

}

#endif // PABACKEND_H
