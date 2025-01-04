#include "display_st77916_driver.h"

#include <Arduino.h>
#include <ESP_IOExpander.h>
#include <ESP_Panel_Library.h>

#include "display_conf.h"
#include "pin_conf.h"

#define TFT_SPI_FREQ_HZ (50 * 1000 * 1000)

void display_clear(ESP_PanelLcd* display);

ESP_PanelLcd* display_init() {
  // Bus
  ESP_PanelBus_QSPI* bus = new ESP_PanelBus_QSPI(TFT_CS, TFT_SCK, TFT_SDA0,
                                                 TFT_SDA1, TFT_SDA2, TFT_SDA3);
  bus->configQspiFreqHz(TFT_SPI_FREQ_HZ);
  bus->begin();

  // LCD
  auto lcd = new ESP_PanelLcd_ST77916(bus, DISPLAY_COLOR_BITS, TFT_RST);
  lcd->configColorRgbOrder(false);
  lcd->init();
  lcd->reset();
  lcd->begin();
  lcd->invertColor(true);
  lcd->displayOn();
  display_clear(lcd);
  return lcd;
}

bool display_draw_bitmap(ESP_PanelLcd* lcd, const uint8_t* bitmap) {
  uint8_t* buffer = nullptr;

  try {
    // Allocate memory for one line
    buffer = new uint8_t[DISPLAY_RES_WIDTH * 2];
  } catch (std::bad_alloc& e) {
    return false;
  }

  for (int y = 0; y < DISPLAY_RES_HEIGHT; y++) {
    for (int x = 0; x < DISPLAY_RES_WIDTH; x++) {
      buffer[x * 2] = bitmap[y * DISPLAY_RES_WIDTH * 2 + x * 2];
      buffer[x * 2 + 1] = bitmap[y * DISPLAY_RES_WIDTH * 2 + x * 2 + 1];
    }
    bool ret =
        lcd->drawBitmapWaitUntilFinish(0, y, DISPLAY_RES_WIDTH, 1, buffer);
    if (!ret) {
      return false;
    }
  }

  delete[] buffer;
  return true;
}

void display_clear(ESP_PanelLcd* display) {
  int bytes_per_pixel = DISPLAY_COLOR_BITS / 8;
  uint8_t* color_buf = nullptr;

  try {
    // Allocate memory for one line
    color_buf = new uint8_t[DISPLAY_RES_WIDTH * bytes_per_pixel];
  } catch (std::bad_alloc& e) {
    return;
  }

  // Fill the buffer with the specified color
  for (int i = 0; i < DISPLAY_RES_WIDTH; i++) {
    color_buf[i * 2] = 0;
    color_buf[i * 2 + 1] = 0;
  }

  // Draw the color across the entire screen
  bool ret = true;
  for (int j = 0; j < DISPLAY_RES_HEIGHT; j++) {
    ret = display->drawBitmapWaitUntilFinish(0, j, DISPLAY_RES_WIDTH, 1,
                                             color_buf);
    if (!ret) {
      break;
    }
  }

  delete[] color_buf;
}
