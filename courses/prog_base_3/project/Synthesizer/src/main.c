#include "SimpleWaves.h"

#include <SDL.h>

#include <stdlib.h>
#include <stdio.h>

struct AppState {
  
}

void si16_audio_callback(void* userdata, Uint8* stream, int _len){
  size_t len = len / sizeof(Sint16);
  
}

void begin_app_loop(){
  SDL_AudioSpec want, have;
  SDL_AudioDeviceId dev;
  
}

int main(int argc, char* argv[]){
  if(SDL_Init(SDL_INIT_AUDIO) != 0){
    SDL_LogCritical(
		    SDL_LOG_CATEGORY_APPLICATION,
		    "Can't init SDL_Audio: %s",
		    SDL_GetError()
		    );
    exit(EXIT_FAILURE);
  }
  atexit(SDL_Quit);
  
  begin_app_loop();
  
  exit(EXIT_SUCCESS);
}
