#include "lcd_display.h"

#include "display_conf.h"
#include "drivers/display_backlight_driver.h"
#include "drivers/display_driver.h"

void LCDDisplay::begin() {
  lcd = display_init();
  backlight = display_backlight_init();
  setBrightness(75);
}

uint16_t LCDDisplay::width() const { return DISPLAY_RES_WIDTH; }

uint16_t LCDDisplay::height() const { return DISPLAY_RES_HEIGHT; }

void LCDDisplay::setBrightness(const uint8_t brightness) {
  backlight->setBrightness(brightness);
}

void LCDDisplay::sleep() {
  lcd->displayOff();
  backlight->off();
}

void LCDDisplay::wakeUp() {
  lcd->displayOn();
  backlight->on();
}

void LCDDisplay::rotate(const uint16_t degree) {
  switch (degree) {
    case 0:
      lcd->swapXY(false);
      lcd->mirrorX(false);
      lcd->mirrorY(false);
      break;
    case 90:
      lcd->swapXY(true);
      lcd->mirrorX(true);
      lcd->mirrorY(false);
      break;
    case 180:
      lcd->swapXY(false);
      lcd->mirrorX(true);
      lcd->mirrorY(true);
      break;
    case 270:
      lcd->swapXY(true);
      lcd->mirrorX(false);
      lcd->mirrorY(true);
      break;
    default:
      break;
  }
}

void LCDDisplay::drawBitmap(const uint8_t *bitmap, const uint32_t x,
                            const uint32_t y, const uint32_t width,
                            const uint32_t height) const {
  lcd->drawBitmapWaitUntilFinish(x + DISPLAY_OFFSET_X, y + DISPLAY_OFFSET_Y,
                                 width, height, bitmap);
}
