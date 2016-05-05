#ifndef AUDIOGENERATOR_H
#define AUDIOGENERATOR_H

#include <SDL.h>

class AudioGenerator
{
public:
    AudioGenerator();
    ~AudioGenerator();
protected:
    void generate(float* data, int length);
    void play();
    void pause();
private:
    int frequency;
    float period;
    SDL_AudioDeviceID dev;

    static void synth_audio_callback(void* data, Uint8* stream, int length);
};

#endif // AUDIOGENERATOR_H
