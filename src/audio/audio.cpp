#include "audio.h"

#include "audio_conf.h"
#include "drivers/audio_i2s_driver.h"

I2SAudio Audio;

void I2SAudio::begin() {
#if defined(SPEAKER_MUTE_PIN)
  pinMode(SPEAKER_MUTE_PIN, OUTPUT);
#endif
  audio_init();
  unmute();
}

void I2SAudio::mute() const {
#if defined(SPEAKER_MUTE_PIN)
  digitalWrite(SPEAKER_MUTE_PIN, LOW);
#endif
}

void I2SAudio::unmute() const {
#if defined(SPEAKER_MUTE_PIN)
  digitalWrite(SPEAKER_MUTE_PIN, HIGH);
#endif
}

const float_t MAX_AMPLITUDE = 32767;
void I2SAudio::buzz(const float_t frequency, const float_t duration,
                    const uint8_t volume) const {
  const int samples = AUDIO_OUT_SAMPLE_RATE * duration;
  const uint16_t bufferSize = samples * sizeof(int16_t) * AUDIO_OUT_CHANNELS;
  int16_t buffer[bufferSize / sizeof(int16_t)];
  const float_t amplitude = MAX_AMPLITUDE * volume / 100;

  for (int i = 0; i < samples; i++) {
    int16_t pcmValue = (int16_t)(amplitude * sin(2 * PI * frequency * i /
                                                 AUDIO_OUT_SAMPLE_RATE));
    if (AUDIO_OUT_CHANNELS == 1) {
      buffer[i] = pcmValue;
    } else if (AUDIO_OUT_CHANNELS == 2) {
      buffer[2 * i] = pcmValue;
      buffer[2 * i + 1] = pcmValue;
    }
  }

  write(buffer, bufferSize);
}

void I2SAudio::playSystemSound(const SystemSound sound,
                               const uint8_t volume) const {
  switch (sound) {
    case SYSTEM_SOUND_HIGHER_BEEP:
      buzz(NOTE_MI * 7, 0.05, volume);
      break;

    case SYSTEM_SOUND_LOWER_BEEP:
      buzz(NOTE_DO * 7, 0.05, volume);
      break;

    case SYSTEM_SOUND_DOUBLE_BEEP:
      buzz(NOTE_MI * 7, 0.05, volume);
      delay(50);
      buzz(NOTE_MI * 7, 0.05, volume);
      break;

    case SYSTEM_SOUND_STARTUP:
      buzz(NOTE_MI * 7, 0.1, volume);
      buzz(NOTE_DO * 7, 0.1, volume);
      buzz(NOTE_RE * 7, 0.1, volume);
      buzz(NOTE_SO * 7, 0.1, volume);
      break;

    default:
      break;
  }
}

size_t I2SAudio::write(int16_t* data, size_t length) const {
  size_t bytesWritten;
  i2s_write(AUDIO_OUT, data, length, &bytesWritten, portMAX_DELAY);
  return bytesWritten;
}

size_t I2SAudio::read(int16_t* data, size_t length) const {
  size_t bytesRead;
  i2s_read(AUDIO_IN, data, length, &bytesRead, portMAX_DELAY);
  return bytesRead;
}
