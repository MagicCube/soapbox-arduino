#include "st77916_display_driver.h"

#include "device_conf.h"

#define TFT_SPI_FREQ_HZ (50 * 1000 * 1000)

void st77916_clear(ESP_PanelLcd_ST77916* lcd);

ESP_PanelLcd_ST77916* st77916_init_lcd() {
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
  st77916_clear(lcd);
  return lcd;
}

ESP_PanelBacklight* st77916_init_backlight() {
  ledc_timer_config_t ledc_timer = {.speed_mode = LEDC_LOW_SPEED_MODE,
                                    .duty_resolution = LEDC_TIMER_13_BIT,
                                    .timer_num = LEDC_TIMER_0,
                                    .freq_hz = 5000,
                                    .clk_cfg = LEDC_AUTO_CLK};
  ESP_ERROR_CHECK(ledc_timer_config(&ledc_timer));

  ledc_channel_config_t ledc_channel = {.gpio_num = (TFT_BLK),
                                        .speed_mode = LEDC_LOW_SPEED_MODE,
                                        .channel = LEDC_CHANNEL_0,
                                        .intr_type = LEDC_INTR_DISABLE,
                                        .timer_sel = LEDC_TIMER_0,
                                        .duty = 0,
                                        .hpoint = 0};
  ESP_ERROR_CHECK(ledc_channel_config(&ledc_channel));

  auto backlight = new ESP_PanelBacklight(ledc_timer, ledc_channel);
  backlight->begin();
  backlight->off();
  backlight->on();
  return backlight;
}

bool st77916_draw_bitmap(ESP_PanelLcd_ST77916* lcd, const uint8_t* bitmap) {
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

void st77916_clear(ESP_PanelLcd_ST77916* lcd) {
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
    ret = lcd->drawBitmapWaitUntilFinish(0, j, DISPLAY_RES_WIDTH, 1, color_buf);
    if (!ret) {
      break;
    }
  }

  delete[] color_buf;
}
