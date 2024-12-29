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

uint16_t I2SSound::sampleRate() const { return RECORDING_SAMPLE_RATE; }

uint8_t I2SSound::bitPerSample() const { return RECORDING_BITS_PER_SAMPLE; }

uint8_t I2SSound::speakerChannels() const { return SPEAKER_CHANNELS; }

void I2SSound::mute() const { digitalWrite(SPEAKER_MUTE_PIN, LOW); }

void I2SSound::unmute() const { digitalWrite(SPEAKER_MUTE_PIN, HIGH); }

const float_t MAX_AMPLITUDE = 32767;
void I2SSound::buzz(const float_t frequency, const float_t duration,
                    const uint8_t volume, const boolean wait) const {
  const int samples = sampleRate() * duration;
  const uint16_t bufferSize = samples * sizeof(int16_t) * speakerChannels();
  int16_t buffer[bufferSize / sizeof(int16_t)];
  const float_t amplitude = MAX_AMPLITUDE * volume / 100;

  for (int i = 0; i < samples; i++) {
    int16_t pcmValue =
        (int16_t)(amplitude * sin(2 * PI * frequency * i / sampleRate()));
    if (speakerChannels() == 1) {
      buffer[i] = pcmValue;
    } else if (speakerChannels() == 2) {
      buffer[2 * i] = pcmValue;
      buffer[2 * i + 1] = pcmValue;
    }
  }

  write(buffer, bufferSize, wait);
}

void I2SSound::playSystemSound(const SystemSound sound, const uint8_t volume,
                               const boolean wait) const {
  switch (sound) {
    case SYSTEM_SOUND_SINGLE_BEEP:
      buzz(NOTE_MI * 8, 0.06, volume, wait);
      break;

    case SYSTEM_SOUND_DOUBLE_BEEP:
      buzz(NOTE_MI * 8, 0.03, volume, wait);
      delay(80);
      buzz(NOTE_MI * 8, 0.03, volume, wait);
      break;

    case SYSTEM_SOUND_WELCOME:
      buzz(NOTE_MI * 7, 0.09, volume, wait);
      buzz(NOTE_DO * 7, 0.09, volume, wait);
      buzz(NOTE_RE * 7, 0.09, volume, wait);
      buzz(NOTE_SO * 7, 0.09, volume, wait);
      break;

    default:
      break;
  }
}

size_t I2SSound::write(int16_t* buffer, size_t bufferSize, bool wait) const {
  size_t bytesWritten;
  i2s_write(SPEAKER_I2S_PORT, buffer, bufferSize, &bytesWritten,
            wait ? portMAX_DELAY : 0);
  return bytesWritten;
}
