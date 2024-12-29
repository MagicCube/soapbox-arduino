#pragma once

class I2SSound {
 public:
  void begin();

  void mute();

  void unmute();
};

extern I2SSound Sound;
