#include "audio.h"

I2SAudio Audio;

void I2SAudio::begin() {
  pinMode(SPEAKER_MUTE_PIN, OUTPUT);
  i2s_init_audio_out();
  i2s_init_audio_in();
  unmute();
}

void I2SAudio::mute() const { digitalWrite(SPEAKER_MUTE_PIN, LOW); }

void I2SAudio::unmute() const { digitalWrite(SPEAKER_MUTE_PIN, HIGH); }

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
    case SYSTEM_SOUND_SINGLE_BEEP:
      buzz(NOTE_MI * 8, 0.06, volume);
      break;

    case SYSTEM_SOUND_DOUBLE_BEEP:
      buzz(NOTE_MI * 8, 0.03, volume);
      delay(80);
      buzz(NOTE_MI * 8, 0.03, volume);
      break;

    case SYSTEM_SOUND_WELCOME:
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
