#pragma once

#include <SDL.h>

typedef void (*synth_adsr_callback)(void* data, Uint8* stream, unsigned int length);
