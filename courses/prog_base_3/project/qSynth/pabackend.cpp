#include "pabackend.h"

namespace qSynth{

PABackend::PABackend(IAudioCallback* callback) : cb(callback)
{
    PaError err;
    err = Pa_Initialize();
    if(err!=paNoError){
        throw err;
    }
    err = Pa_OpenDefaultStream(
                &stream,
                0,
                1,
                paFloat32,
                SAMPLE_RATE,
                PA_BACKEND_BUFFER,
                &PABackend::callback,
                this
                );
    if(err!=paNoError){
        throw err;
    }
}

PABackend::~PABackend(){
    PaError err;

    err = Pa_CloseStream(stream);
    if(err!=paNoError){
        throw err;
    }
    err = Pa_Terminate();
    if(err!=paNoError){
        throw err;
    }
}

int PABackend::callback(const void *, void *_out, unsigned long frames,
                    const PaStreamCallbackTimeInfo *, PaStreamCallbackFlags,
                    void *userdata){
    float* out;
    PABackend* self;

    out = (float*)_out;
    self = (PABackend*) userdata;
    self->cb->fillBuffer(out, frames);

    return 0;
}

void PABackend::start(){
    PaError err;

    err = Pa_StartStream(stream);
    if(err){
        throw err;
    }
}
void PABackend::stop(){
    PaError err;
    err = Pa_StopStream(stream);
    if(err!=paNoError) {
        throw err;
    }
}
void PABackend::pause(){
    stop();
}
void PABackend::unpause(){
    start();
}

}
