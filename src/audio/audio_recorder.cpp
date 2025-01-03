#include "audio_recorder.h"

void AudioRecorder::begin() {
  buffer = new CircularBuffer(AUDIO_IN_FRAME_SIZE * AUDIO_IN_FPS * 5);
}

void AudioRecorder::startRecording() {
  if (recording) {
    return;
  }

  buffer->clear();

  recording = true;
}

void AudioRecorder::stopRecording() {
  if (!recording) {
    return;
  }

  recording = false;
}

void AudioRecorder::play() {
  while (true) {
    int16_t data[AUDIO_IN_FRAME_SIZE / sizeof(int16_t)];
    size_t bytesRead = buffer->read((uint8_t*)data, AUDIO_IN_FRAME_SIZE);
    if (bytesRead == 0) {
      break;
    }
    Audio.write(data, bytesRead);
  }
}

void AudioRecorder::update() {
  if (recording) {
    int16_t data[AUDIO_IN_FRAME_SIZE / sizeof(int16_t)];
    size_t bytesRead = Audio.read(data, AUDIO_IN_FRAME_SIZE);
    buffer->write((uint8_t*)data, bytesRead);
  }
}
