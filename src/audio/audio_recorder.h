#pragma once

#include <mx.h>

#include "audio/audio.h"
#include "buffering/circular_buffer.h"

class AudioRecorder {
 public:
  void begin();
  void startRecording();
  void stopRecording();
  void play();
  void update();

  bool isRecording() const { return recording; }

 protected:
  bool recording = false;
  CircularBuffer *buffer;
};
