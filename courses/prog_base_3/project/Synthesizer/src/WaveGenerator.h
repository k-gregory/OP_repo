#pragma once

#include "ADSR.h"
#include "audio_utils.h"

#include <SDL.h>

typedef float (*wave_func)(unsigned int sample_num);

typedef struct WaveGenerator {
  wave_func wave;
  synth_arsr_callback adsr,
  float frequency;
  float amplitude;
  unsigned int pos;
  unsigned int end;
} WaveGenerator;

/**
\brief Inits musical wave generator
\param[out] wg WaveGenerator to be inited
\param[in] wave Function which generates wave
\param[in] HzFreq Wanted wave frequency in hertz
\param[in] adsr Function that generates ADSR curve. Values must be [0..1]
\param[in] amplitude Amplitude of the generated wave
\param[in] sample_rate DSP frequency
\param[in] length Number of samples after which generator does not produces sound
 */
void synth_wg_init(WaveGenerator* wg,
		   wave_func wave,
		   synth_adsr_callback adsr,
		   unsigned HzFreq,
		   float amplitude,
		   unsigned int sample_rate,		   
		   unsigned int length) {
  wg->wave = wave;
  wg->adsr = adsr;
  wg->frequency = synth_get_freq(HzFreq, sample_rate);
  wg->amplitude = amplitude;
  wg->pos = 0;
  wg->end = length;
}

void synth_wg_add_wave_si16(WaveGenerator* wg, Sint16* stream, unsigned int _len){
  register wave_func wave;
  unsigned int pos,i, len;
  float amplitude, frequency;
  
  wave = wg->wave;
  len = SDL_Min(wg->pos + _len, wg->end);
  amplitude = wg->amplitude;
  frequency = wg->frequency;
  pos = wg->pos - 1;

  for(i = 0; i < len; i++){
    stream[i] += amplitude * wave(++pos *
  }
}
