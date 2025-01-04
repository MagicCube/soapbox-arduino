#pragma once

#include "audio/audio.h"
#include "buffering/circular_buffer.h"

class AudioRecorder {
 public:
  void begin();
  void record();
  void stop();
  void play();
  void update();

  bool isRecording() const { return recording; }

 protected:
  bool recording = false;
  bool playing = false;
  CircularBuffer *buffer;
};
