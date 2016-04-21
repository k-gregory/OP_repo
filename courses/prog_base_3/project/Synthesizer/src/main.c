#include "audio_utils.h"

#include <SDL.h>

#include <stdlib.h>
#include <stdio.h>
#include <math.h> /*TODO:Move to file*/

#define WND_WIDTH 1000
#define WND_HEIGHT 400

#define WANTED_FREQUENCY 48000
#define WANTED_SAMPLES 512

/*
 * Contains state of application
 */
struct AppState {
    float sample_time;
    int samples_per_second;
    unsigned int audio_pos;
} app_state = {
    0, 0, 0
};

/*
 * Called each time to fill buffer.
 * Relies on FLOAT32 audio format
 */


void main_sdl_audio_callback(void* data, Uint8* _stream, int _length){
    size_t length, i;
    //float* stream;
    float *stream;
    float frequency;

    stream = (float*) _stream;
    length = _length / sizeof(float);

    for(i = 0; i < length; i++){
        float time = app_state.audio_pos * app_state.sample_time;
        float sin_v = sinf(2*M_PI*time*450);
        stream[i] = sin_v*sinf(2*M_PI*sinf(time*400)*100);
        ++app_state.audio_pos;
    }
}

SDL_AudioDeviceID synth_init_audio_system(){
    SDL_AudioSpec want;
    SDL_AudioSpec have;
    SDL_AudioDeviceID dev;

    SDL_zero(want);
    want.freq = WANTED_FREQUENCY;
    want.format  = AUDIO_F32;
    want.channels = 1;
    want.samples = WANTED_SAMPLES;
    want.callback = main_sdl_audio_callback;

    dev = SDL_OpenAudioDevice(NULL, 0, &want, &have, SDL_AUDIO_ALLOW_FREQUENCY_CHANGE);
    app_state.samples_per_second = have.freq;
    app_state.sample_time = 1.f / app_state.samples_per_second;

    return dev;
}

void app_loop(SDL_Renderer* renderer){
  SDL_AudioDeviceID dev;
  SDL_Event ev;

  dev = synth_init_audio_system();
  SDL_PauseAudioDevice(dev, SDL_FALSE);

  while(1){
      while(SDL_PollEvent(&ev)){
          if(ev.type == SDL_QUIT)
              goto LOOP_EXIT;
      }
  }
  LOOP_EXIT:
  return;
}

int main(int argc, char* argv[]){
    SDL_Window* wnd;
    SDL_Renderer* renderer;

    if(SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO) != 0){
        SDL_LogCritical(
                    SDL_LOG_CATEGORY_APPLICATION,
                    "Can't init SDL_Audio: %s",
                    SDL_GetError());
        exit(EXIT_FAILURE);
    }
    atexit(SDL_Quit);

    if(SDL_CreateWindowAndRenderer(WND_WIDTH,WND_HEIGHT,SDL_WINDOW_SHOWN,&wnd,&renderer)!=0){
        SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION,
                        "Can't create SDL renderer: %s",
                        SDL_GetError());
    }

    app_loop(renderer);
  
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(wnd);

    exit(EXIT_SUCCESS);
}

