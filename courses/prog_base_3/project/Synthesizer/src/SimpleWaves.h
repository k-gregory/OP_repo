#pragma once

#include <SDL.h>
#include <stdlib.h>


typedef struct WaveInfo {
  float frequency;
  float amplitude;
  unsigned int pos;
} WaveInfo;

/**
\brief Initializes WaveInfo
\param[out] w Wave to initialize
\param[in] HzFreq Wanted frequency, in hertz
\param[in] amplitude Wanted amplitude
\param[in] samples_per_second DSP frequency
*/
void wave_info_init(WaveInfo* w, float amplitude, unsigned int HzFreq, unsigned int samples_per_second);

/**
\brief ADDS sin wave to buffer
ADDS one-channel wave to buffer of Signed Int 16-byte format
To generate pure sine wave buffer MUST be filled with silence
\param[in] wi Wave info
\param[in] len Number of samples
\param[out] stream Stream to write samples
*/
void gen_sin_wave_si16(WaveInfo* wi, size_t len, Sint16* stream);
/**
\brief ADDS wave to buffer. Same as wave_info_init but changes amplitude
ADDS one-channel wave to buffer of Signed Int 16-byte format
To generate pure sine wave buffer MUST be filled with silence
\param[in] wi Wave info
\param[in] len Number of samples
\param[in] amplitude Amplitude of wave
\param[out] stream Stream to write sample 
 */
void gen_sin_wave_si16_a(WaveInfo* wi, size_t len, Sint16* stream, float amplitude);

/**
\brief Generates silence
Generates silence. Ignores previous stream values
 */
void gen_silence_si16(Sint16* stream, size_t len);
