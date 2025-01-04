#include "audio_recorder.h"

#include "audio_conf.h"

void AudioRecorder::begin() {
  buffer = new CircularBuffer(AUDIO_IN_FRAME_SIZE * AUDIO_IN_FPS * 5);
}

void AudioRecorder::record() {
  if (recording || playing) {
    stop();
  }

  buffer->clear();

  recording = true;
}

void AudioRecorder::stop() {
  playing = false;
  recording = false;
}

void AudioRecorder::play() {
  if (recording || playing) {
    stop();
  }

  playing = true;
}

void AudioRecorder::update() {
  int16_t data[AUDIO_IN_FRAME_SIZE / sizeof(int16_t)];
  if (recording) {
    size_t bytesRead = Audio.read(data, AUDIO_IN_FRAME_SIZE);
    buffer->write((uint8_t*)data, bytesRead);
    if (bytesRead == 0) {
      stop();
    }
  } else if (playing) {
    size_t bytesRead = buffer->read((uint8_t*)data, AUDIO_OUT_FRAME_SIZE);
    Audio.write(data, bytesRead);
    if (bytesRead == 0) {
      stop();
    }
  }
}
