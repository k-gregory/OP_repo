#include "SDL.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

size_t freq;

void test_audio_callback(void* data, Uint8* stream, int len) {
  for(size_t i = 0; i < len; i++)
    stream[i] = rand();
}

void play_something() {
  SDL_AudioSpec want, have;
  SDL_AudioDeviceID dev;
  SDL_zero(want);
  want.freq = 48000;
  want.format = AUDIO_S16;
  want.channels = 2;
  want.samples = 4096;
  want.callback = test_audio_callback;

  dev = SDL_OpenAudioDevice(NULL, 0, &want, &have, SDL_AUDIO_ALLOW_FREQUENCY_CHANGE);
  if(dev == 0)
    printf("Failed to open audio: %s\n",SDL_GetError());
  else {
    freq = have.freq;
    SDL_PauseAudioDevice(dev,0);
    SDL_Delay(5000);
    SDL_CloseAudioDevice(dev);
  }
}

int main(int argc, char* argv[]){
  srand(time(NULL));
  if(SDL_Init(SDL_INIT_AUDIO) != 0) {
    fprintf(stderr,
	    "\nUnable to initialize SDL: %s\n",
	    SDL_GetError());
    return EXIT_FAILURE;
  }
  atexit(SDL_Quit);

  play_something();
  
  return EXIT_SUCCESS;
}
