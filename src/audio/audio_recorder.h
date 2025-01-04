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

  bool isPlaying() const { return playing; }
  bool isRecording() const { return recording; }

 protected:
  bool playing = false;
  bool recording = false;
  CircularBuffer *buffer;
};
