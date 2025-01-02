#pragma once

#include <Arduino.h>
#include <lvgl.h>

#include "mx_font.h"

class MXObject {
 public:
  MXObject(lv_obj_t* lv_obj);

  inline MXObject& label(const char* text = nullptr,
                         const FontSize fontSize = FONT_SIZE_DEFAULT) {
    lv_obj_t* lv_label = lv_label_create(lv_obj);
    MXObject* label = new MXObject(lv_label);
    if (text != nullptr) {
      label->text(text);
    }
    label->text(fontSize);
    return *label;
  }

  inline MXObject& button(const char* text = nullptr,
                          const FontSize fontSize = FONT_SIZE_DEFAULT) {
    lv_obj_t* lv_button = lv_btn_create(lv_obj);
    MXObject* button = new MXObject(lv_button);
    lv_obj_t* lv_label = lv_label_create(lv_button);
    if (text != nullptr) {
      button->text(text);
    }
    button->text(fontSize);
    return *button;
  }

  // Size
  MXObject& w(const int32_t width);
  MXObject& h(const int32_t height);
  MXObject& size(const int32_t width, const int32_t height);
  MXObject& size(const int32_t length);
  MXObject& w_percent(const int32_t width);
  MXObject& h_percent(const int32_t height);
  MXObject& size_percent(const int32_t width, const int32_t height);
  MXObject& w_fit();
  MXObject& h_fit();
  MXObject& size_fit();
  MXObject& w_full();
  MXObject& h_full();
  MXObject& size_full();

  // Position
  MXObject& x(const int32_t x);
  MXObject& y(const int32_t y);
  MXObject& pos(const int32_t x, const int32_t y);

  // Padding
  MXObject& p(const lv_coord_t padding);
  MXObject& p(const lv_coord_t padding_x, const lv_coord_t padding_y);
  MXObject& p_x(const lv_coord_t padding_x);
  MXObject& p_y(const lv_coord_t padding_y);

  // Align
  MXObject& align(const lv_align_t align);
  MXObject& center();
  MXObject& center_x();
  MXObject& center_y();

  // Background
  MXObject& bg(const lv_color_t color);

  // Font
  MXObject& font(const lv_font_t* font);

  // Text
  MXObject& text(const char* text);
  MXObject& text_format(const char* format, ...);
  MXObject& text(const FontSize size);
  MXObject& text(const lv_color_t color);
  MXObject& text_align(const lv_text_align_t align);
  MXObject& text_letter_space(const lv_coord_t space);

  // Corner
  MXObject& rounded(const lv_coord_t radius);
  MXObject& rounded_full();

  // Clip
  MXObject& clip_content();

  // Visibility
  MXObject& show();
  MXObject& hide();
  MXObject& toggle(bool visible);

 protected:
  lv_obj_t* lv_obj;

  lv_obj_t* get_text_obj();
};

MXObject* mx();
