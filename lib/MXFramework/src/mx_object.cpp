#include "mx_object.h"

MXObject::MXObject(lv_obj_t* obj) : lv_obj(obj) {}

MXObject& MXObject::w(const int32_t width) {
  // lv_obj_set_width(lv_obj, width);
  return *this;
}

MXObject& MXObject::h(const int32_t height) {
  lv_obj_set_height(lv_obj, height);
  return *this;
}

MXObject& MXObject::size(const int32_t width, const int32_t height) {
  lv_obj_set_size(lv_obj, width, height);
  return *this;
}

MXObject& MXObject::size(const int32_t length) {
  size(length, length);
  return *this;
}

MXObject& MXObject::w_percent(const int32_t width) {
  lv_obj_set_width(lv_obj, lv_pct(width));
  return *this;
}

MXObject& MXObject::h_percent(const int32_t height) {
  lv_obj_set_height(lv_obj, lv_pct(height));
  return *this;
}

MXObject& MXObject::size_percent(const int32_t width, const int32_t height) {
  lv_obj_set_size(lv_obj, lv_pct(width), lv_pct(height));
  return *this;
}

MXObject& MXObject::w_fit() {
  lv_obj_set_width(lv_obj, LV_SIZE_CONTENT);
  return *this;
}

MXObject& MXObject::h_fit() {
  lv_obj_set_height(lv_obj, LV_SIZE_CONTENT);
  return *this;
}

MXObject& MXObject::size_fit() {
  lv_obj_set_size(lv_obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
  return *this;
}

MXObject& MXObject::w_full() {
  w_percent(100);
  return *this;
}

MXObject& MXObject::h_full() {
  h_percent(100);
  return *this;
}

MXObject& MXObject::size_full() {
  size_percent(100, 100);
  return *this;
}

MXObject& MXObject::x(const int32_t x) {
  lv_obj_set_x(lv_obj, x);
  return *this;
}

MXObject& MXObject::y(const int32_t y) {
  lv_obj_set_y(lv_obj, y);
  return *this;
}

MXObject& MXObject::pos(const int32_t x, const int32_t y) {
  lv_obj_set_pos(lv_obj, x, y);
  return *this;
}

MXObject& MXObject::p(const lv_coord_t padding) {
  lv_obj_set_style_pad_all(lv_obj, padding, LV_PART_MAIN);
  return *this;
}

MXObject& MXObject::p(const lv_coord_t padding_x, const lv_coord_t padding_y) {
  p_x(padding_x);
  p_y(padding_y);
  return *this;
}

MXObject& MXObject::p_x(const lv_coord_t padding_x) {
  lv_obj_set_style_pad_hor(lv_obj, padding_x, LV_PART_MAIN);
  return *this;
}

MXObject& MXObject::p_y(const lv_coord_t padding_y) {
  lv_obj_set_style_pad_ver(lv_obj, padding_y, LV_PART_MAIN);
  return *this;
}

MXObject& MXObject::align(const lv_align_t align) {
  lv_obj_align(lv_obj, align, 0, 0);
  return *this;
}

MXObject& MXObject::center() {
  align(LV_ALIGN_CENTER);
  return *this;
}

MXObject& MXObject::center_x() {
  align(LV_ALIGN_TOP_MID);
  return *this;
}

MXObject& MXObject::center_y() {
  align(LV_ALIGN_LEFT_MID);
  return *this;
}

MXObject& MXObject::bg(const lv_color_t color) {
  lv_obj_set_style_bg_color(lv_obj, color, LV_PART_MAIN);
  return *this;
}

MXObject& MXObject::font(const lv_font_t* font) {
  auto text_obj = get_text_obj();
  if (text_obj != nullptr) {
    lv_obj_set_style_text_font(text_obj, font, LV_PART_MAIN);
  }
  return *this;
}

MXObject& MXObject::text(const char* text) {
  auto text_obj = get_text_obj();
  if (text_obj != nullptr) {
    lv_label_set_text(text_obj, text);
  }
  return *this;
}

MXObject& MXObject::text_format(const char* format, ...) {
  va_list args;
  va_start(args, format);
  auto text_obj = get_text_obj();
  if (text_obj != nullptr) {
    lv_label_set_text_fmt(text_obj, format, args);
  }
  va_end(args);
  return *this;
}

MXObject& MXObject::text(const FontSize size) {
  switch (size) {
    case FONT_SIZE_14:
      font(&lv_font_montserrat_14);
      break;
    case FONT_SIZE_16:
      font(&lv_font_montserrat_16);
      break;
    case FONT_SIZE_18:
      font(&lv_font_montserrat_18);
      break;
    case FONT_SIZE_20:
      font(&lv_font_montserrat_20);
      break;
    case FONT_SIZE_24:
      font(&lv_font_montserrat_24);
      break;
    case FONT_SIZE_30:
      font(&lv_font_montserrat_30);
      break;
    case FONT_SIZE_36:
      font(&lv_font_montserrat_36);
      break;
    case FONT_SIZE_48:
      font(&lv_font_montserrat_48);
      break;
  }
  return *this;
}

MXObject& MXObject::text(const lv_color_t color) {
  auto text_obj = get_text_obj();
  if (text_obj != nullptr) {
    lv_obj_set_style_text_color(text_obj, color, LV_PART_MAIN);
  }
  return *this;
}

MXObject& MXObject::text_align(const lv_text_align_t align) {
  auto text_obj = get_text_obj();
  if (text_obj != nullptr) {
    lv_obj_set_style_text_align(text_obj, align, LV_PART_MAIN);
  }
  return *this;
}

MXObject& MXObject::text_letter_space(const lv_coord_t space) {
  auto text_obj = get_text_obj();
  if (text_obj != nullptr) {
    lv_obj_set_style_text_letter_space(text_obj, space, LV_PART_MAIN);
  }
  return *this;
}

MXObject& MXObject::rounded(const lv_coord_t radius) {
  lv_obj_set_style_radius(lv_obj, radius, LV_PART_MAIN);
  return *this;
}

MXObject& MXObject::rounded_full() {
  rounded(LV_RADIUS_CIRCLE);
  return *this;
}

MXObject& MXObject::clip_content() {
  lv_obj_set_style_clip_corner(lv_obj, true, LV_PART_MAIN);
  return *this;
}

MXObject& MXObject::show() {
  lv_obj_clear_flag(lv_obj, LV_OBJ_FLAG_HIDDEN);
  return *this;
}

MXObject& MXObject::hide() {
  lv_obj_add_flag(lv_obj, LV_OBJ_FLAG_HIDDEN);
  return *this;
}

MXObject& MXObject::toggle(bool visible) {
  if (visible) {
    show();
  } else {
    hide();
  }
  return *this;
}

lv_obj_t* MXObject::get_text_obj() {
  if (lv_obj_check_type(lv_obj, &lv_button_class)) {
    return lv_obj_get_child(lv_obj, 0);
  } else if (lv_obj_check_type(lv_obj, &lv_label_class)) {
    return lv_obj;
  }
  return nullptr;
}

MXObject* mx() {
  MXObject* obj = new MXObject(lv_scr_act());
  return obj;
}
