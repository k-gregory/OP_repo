#include "SimpleWaves.h"
#include "audio_utils.h"

#include <stdlib.h>
#include <math.h>

void wave_info_init(WaveInfo* in,
		    float amplitude,
		    unsigned int HzFreq,
		    unsigned int samples_per_second){
  in->frequency = synth_get_freq(HzFreq, samples_per_second);
  in->amplitude = amplitude;
  in->pos = 0;
}

static inline void i_gen_sin_wave_si16(Sint16* stream,
				       size_t len,
				       unsigned int pos,
				       float frequency,
				       float amplitude){
  size_t i;
  
  --pos;
  for(i = 0; i < len; ++i){
    stream[i] = sin(++pos * frequency) * amplitude;
  }
}

void gen_sin_wave_si16(WaveInfo* wi, size_t len, Sint16* stream){
  i_gen_sin_wave_si16(stream, len, wi->pos, 2 * M_PI * wi->frequency, wi->amplitude);
  wi->pos += len;
}

void gen_sin_wave_si16_a(WaveInfo* wi, size_t len, Sint16* stream, float amplitude){
  i_gen_sin_wave_si16(stream, len, wi->pos, 2 * M_PI * wi->frequency, wi->amplitude * amplitude);
  wi->pos += len;
}

void gen_silence_si16(Sint16* stream, size_t len) {
  size_t i;
  for(i = 0 ; i  < len; i++)
    stream[i] = 0;
}
