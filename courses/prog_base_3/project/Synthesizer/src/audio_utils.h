#pragma once

/**
\param[in] HzFreq Wanted frequency in hertz
\param[in] samples_per_second DSP frequency
\returns Value which can be multiplied by sample index to get wave time argument
 */
float synth_get_freq(unsigned int HzFreq,
		     unsigned int samples_per_second);
