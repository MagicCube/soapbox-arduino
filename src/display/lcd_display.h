#pragma once

#include <Arduino.h>
#include <ESP_IOExpander.h>
#include <ESP_Panel_Library.h>

class LCDDisplay {
 public:
  void begin();

  uint16_t width() const;

  uint16_t height() const;

  void setBrightness(const uint8_t angle);

  void sleep();

  void wakeUp();

  void rotate(const uint16_t angle);

  void drawBitmap(const uint8_t* bitmap, const uint32_t x, const uint32_t y,
                  const uint32_t width, const uint32_t height) const;

 protected:
  ESP_PanelLcd_ST77916* lcd = nullptr;
  ESP_PanelBacklight* backlight = nullptr;
};
