#pragma once

#include <Arduino.h>

#include "drivers/i2s_driver.h"
#include "notes.h"

enum SystemSound {
  SYSTEM_SOUND_SINGLE_BEEP,
  SYSTEM_SOUND_DOUBLE_BEEP,
  SYSTEM_SOUND_WELCOME,
};

class I2SAudio {
 public:
  void begin();

  void mute() const;

  void unmute() const;

  size_t write(int16_t* data, size_t length) const;

  void buzz(const float_t frequency, const float_t duration,
            const uint8_t volume = 100) const;

  void playSystemSound(const SystemSound sound, const uint8_t volume = 5) const;
};

extern I2SAudio Audio;
