#include "audiogenerator.h"

#include <SDL.h>
#include <stdexcept>

#define WANTED_FREQUENCY 48000
#define WANTED_SAMPLES 512

void AudioGenerator::synth_audio_callback(void* data, Uint8* stream, int length){
    AudioGenerator *self = (AudioGenerator*) data;
    self->generate((float*) stream, length/sizeof(float));
}

void AudioGenerator::generate(float *data, int length){

}

void AudioGenerator::play(){
    SDL_PauseAudioDevice(dev, 1);
}
void AudioGenerator::pause(){
    SDL_PauseAudioDevice(dev, 0);
}

AudioGenerator::AudioGenerator()
{
    SDL_AudioSpec want,have;
    SDL_AudioDeviceID dev;

    SDL_zero(want);
    want.freq = WANTED_FREQUENCY;
    want.format = AUDIO_F32;
    want.channels = 1;
    want.samples = WANTED_SAMPLES;
    want.callback = &AudioGenerator::synth_audio_callback;
    want.userdata = this;

    dev = SDL_OpenAudioDevice(nullptr, 0, &want, &have, SDL_AUDIO_ALLOW_FREQUENCY_CHANGE);
    if(dev<0) throw std::runtime_error(SDL_GetError());

    this->frequency = have.freq;
    this->period = 1.f/have.freq;
}

AudioGenerator::~AudioGenerator(){
    SDL_CloseAudioDevice(dev);
}
