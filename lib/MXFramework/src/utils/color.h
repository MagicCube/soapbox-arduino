#include <lvgl.h>

inline lv_color_t rgb(uint8_t r, uint8_t g, uint8_t b) {
  return lv_color_make(r, g, b);
}

inline lv_color_t rgb(uint32_t rgb) {
  return lv_color_make((rgb >> 16) & 0xFF, (rgb >> 8) & 0xFF, rgb & 0xFF);
}
