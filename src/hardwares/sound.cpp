#include "sound.h"

#include <Arduino.h>

#include "device_conf.h"
#include "drivers/i2s_driver.h"

I2SSound Sound;

void I2SSound::begin() {
  pinMode(SPEAKER_MUTE_PIN, OUTPUT);
  i2s_init_speaker();
  i2s_init_mic();
  unmute();
}

void I2SSound::mute() { digitalWrite(SPEAKER_MUTE_PIN, LOW); }

void I2SSound::unmute() { digitalWrite(SPEAKER_MUTE_PIN, HIGH); }
