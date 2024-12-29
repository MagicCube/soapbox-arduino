#pragma once

#define RECORDING_SAMPLE_RATE 16000
#define RECORDING_BITS_PER_SAMPLE 16

#include <driver/i2s.h>

void i2s_init_speaker();
void i2s_init_mic();
