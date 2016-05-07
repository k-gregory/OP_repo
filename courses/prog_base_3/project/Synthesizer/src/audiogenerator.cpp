#include "audiogenerator.h"

#include <SDL.h>
#include <stdexcept>
#include <cmath>
#include <iostream>

#define WANTED_FREQUENCY 48000
//TODO: Determine hardware supported samples
#define WANTED_SAMPLES 512

int n = 0;
int nn =0;

void AudioGenerator::synth_audio_callback(void* data, Uint8* stream, int length){
    AudioGenerator *self = (AudioGenerator*) data;
    self->generate((float*) stream, length/sizeof(float));
}

void AudioGenerator::generate(float *data, int length){
    unsigned long int last = pos + length;
    for(;pos < last; pos++)
        *data++ = std::sin(sample_time*pos*2*3.14*600);
}

void AudioGenerator::play(){
    SDL_PauseAudioDevice(dev, 0);
}
void AudioGenerator::pause(){
    SDL_PauseAudioDevice(dev, 1);
}

AudioGenerator::AudioGenerator(){
    SDL_AudioSpec want,have;

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
    this->sample_time = 1.f/have.freq;
}

AudioGenerator::~AudioGenerator(){
    SDL_CloseAudioDevice(dev);
}
