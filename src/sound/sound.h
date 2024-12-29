#pragma once

#include <Arduino.h>

#include "notes.h"

enum SystemSound {
  SYSTEM_SOUND_SINGLE_BEEP,
  SYSTEM_SOUND_DOUBLE_BEEP,
  SYSTEM_SOUND_WELCOME,
};

class I2SSound {
 public:
  void begin();

  uint16_t sampleRate() const;
  uint8_t bitPerSample() const;
  uint8_t channelsOfSpeaker() const;

  void mute() const;

  void unmute() const;

  size_t write(int16_t* buffer, size_t bufferSize, bool wait = true) const;

  void buzz(const float_t frequency, const float_t duration,
            const uint8_t volume = 100, bool wait = true) const;

  void playSystemSound(const SystemSound sound, const uint8_t volume = 1,
                       bool wait = true) const;
};

extern I2SSound Sound;
