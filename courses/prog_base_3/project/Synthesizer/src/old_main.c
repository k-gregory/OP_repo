#include "SDL.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

#define FREQ 200

unsigned int audio_pos;
int audio_len;
int al_s;
float audio_frequency;
float audio_volume;

#define COEF() (1.f - 1.f * audio_pos / al_s)

typedef struct WaveData{
  float frequency;
  unsigned int pos;
  unsigned int pos_period;
} WaveData;

void gena_sin_wave_si16(WaveData* wave_data, Sint16* stream, int len){
  for(unsigned int i = 0 ; i < len; i++){
    stream[i] = audio_volume * sin(2.f * M_PI * wave_data->frequency * wave_data->pos++);
  }
  if(wave_data->pos > wave_data->pos_period)
    wave_data->pos = wave_data->pos % wave_data->pos_period;
}

void test_audio_callback(void* data, Uint8* _stream, int len) {
  //len = len / sizeof(Sint16);
  Sint16* stream = (Sint16*) _stream;
  gena_sin_wave_si16(data, stream, len);
  /*
  for(int i = 0; i < len; i++){
    //Harmonics =)
    stream[i]  = audio_volume * sin (2.f * M_PI * audio_pos * audio_frequency);
    //stream[i] += audio_volume * sin(2.f * 2 * M_PI * audio_pos * audio_frequency)/3;
    stream[i] += audio_volume * sin(2.f * 3 * M_PI * audio_pos * audio_frequency)/3;
    stream[i] += audio_volume * sin(2.f * 4 * M_PI * audio_pos * audio_frequency)/3;
    //stream[i] += audio_volume * sin(2.f * 5 * M_PI * audio_pos * audio_frequency);
    //stream[i] += audio_volume * sin(2.f * 6 * M_PI * audio_pos * audio_frequency);
    //stream[i] += audio_volume * sin(2.f * 7 * M_PI * audio_pos * audio_frequency);
    //stream[i] += audio_volume * sin(2.f * 8 * M_PI * audio_pos * audio_frequency)/2;
    //stream[i] += audio_volume * sin(2.f * 9 * M_PI * audio_pos * audio_frequency);
    //stream[i] += audio_volume * sin(2.f * 10* M_PI * audio_pos * audio_frequency);
    
    stream[i] = stream[i] * COEF() * COEF();
   
    audio_pos++;
  }*/
  audio_len -= len/2;
}

void play_something() {
  SDL_AudioSpec want, have;
  SDL_AudioDeviceID dev;
  WaveData sine_wave;

  sine_wave.pos = 0;
  sine_wave.pos_period = 999999999;//TODO: Calculate
  
  SDL_zero(want);
  want.freq = 48000;
  want.format = AUDIO_S16;
  want.channels = 2;
  want.samples = 4096;
  want.callback = test_audio_callback;
  want.userdata = &sine_wave;

  dev = SDL_OpenAudioDevice(NULL, 0, &want, &have, SDL_AUDIO_ALLOW_FREQUENCY_CHANGE);
  if(dev == 0)
    printf("Failed to open audio: %s\n",SDL_GetError());
  else {
    audio_len = have.freq * 5;
    al_s = audio_len;
    audio_pos = 0;
    audio_frequency = 1.0 * FREQ / have.freq;
    sine_wave.frequency = 1.0 * FREQ / have.freq;
    audio_volume = 6000;
      
    SDL_PauseAudioDevice(dev,0);
    while(audio_len > 0)
      SDL_Delay(500);
    SDL_CloseAudioDevice(dev);
  }
}

int main(int argc, char* argv[]){
  assert(sizeof(Sint16) == 2);
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
