#ifndef AUDIOGENERATOR_H
#define AUDIOGENERATOR_H

#include <SDL.h>
#include <atomic>

class AudioGenerator
{
public:
    AudioGenerator();
    ~AudioGenerator();
    void play();
    void pause();
    std::atomic_flag bus_spinlock = ATOMIC_FLAG_INIT;
protected:
    void generate(float* data, int length);
private:
    int frequency;
    float sample_time;
    unsigned long int pos = 0;
    SDL_AudioDeviceID dev;

    static void synth_audio_callback(void* data, Uint8* stream, int length);
};

#endif // AUDIOGENERATOR_H
