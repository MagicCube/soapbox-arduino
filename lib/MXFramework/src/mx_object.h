#pragma once

#include <Arduino.h>
#include <lvgl.h>

#include "mx_event.h"
#include "mx_font.h"
#include "utils/color.h"

class MXScene;

class MXObject {
 public:
  MXObject(lv_obj_t* lv_obj = nullptr);

  inline MXObject& object(const int32_t width = -1, const int32_t height = -1) {
    lv_obj_t* lv_object = lv_obj_create(lv_obj);
    MXObject* object = new MXObject(lv_object);
    if (width >= 0) {
      object->w(width);
    }
    if (height >= 0) {
      object->h(height);
    }
    return *object;
  }

  inline MXObject& label(const char* text = nullptr,
                         const MXFontSize fontSize = MX_FONT_SIZE_DEFAULT) {
    lv_obj_t* lv_label = lv_label_create(lv_obj);
    MXObject* label = new MXObject(lv_label);
    if (text != nullptr) {
      label->text(text);
    }
    label->text(fontSize);
    return *label;
  }

  inline MXObject& button(const char* text = nullptr,
                          const MXFontSize fontSize = MX_FONT_SIZE_DEFAULT) {
    lv_obj_t* lv_button = lv_btn_create(lv_obj);
    MXObject* button = new MXObject(lv_button);
    lv_obj_t* lv_label = lv_label_create(lv_button);
    lv_obj_align(lv_label, LV_ALIGN_CENTER, 0, 0);
    if (text != nullptr) {
      button->text(text);
    }
    button->text(fontSize);
    return *button;
  }

  inline lv_obj_t* lv_object() { return lv_obj; }

  // Size
  MXObject& w(const int32_t width);
  MXObject& h(const int32_t height);
  MXObject& size(const int32_t width, const int32_t height);
  inline MXObject& size(const int32_t length) {
    return this->size(length, length);
  }
  MXObject& w_percent(const int32_t width);
  MXObject& h_percent(const int32_t height);
  MXObject& size_percent(const int32_t width, const int32_t height);
  inline MXObject& size_percent(const int32_t percent) {
    return this->size_percent(percent, percent);
  }
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
  inline MXObject& center() { return this->align(LV_ALIGN_CENTER); }
  inline MXObject& center_x() { return this->align(LV_ALIGN_TOP_MID); }
  inline MXObject& center_y() { return this->align(LV_ALIGN_LEFT_MID); }

  // Background
  MXObject& bg(const lv_color_t color);
  inline MXObject& bg(const uint32_t color) { return this->bg(rgb(color)); }

  // Font
  MXObject& font(const lv_font_t* font);

  // Text
  MXObject& text(const char* text);
  MXObject& text_format(const char* format, ...);

  // Text Style
  MXObject& text(const MXFontSize size);
  MXObject& text(const lv_color_t color);
  inline MXObject& text(const uint32_t color) { return this->text(rgb(color)); }
  MXObject& text_align(const lv_text_align_t align);
  inline MXObject& text_center() {
    return this->text_align(LV_TEXT_ALIGN_CENTER);
  }
  MXObject& text_letter_space(const lv_coord_t space);

  // Corner
  MXObject& rounded(const lv_coord_t radius);
  inline MXObject& rounded_full() { return this->rounded(LV_RADIUS_CIRCLE); }

  // Clip
  MXObject& clip_content();

  // Visibility
  MXObject& show();
  MXObject& hide();
  MXObject& toggle();
  inline MXObject& toggle(bool visible) {
    if (visible) {
      show();
    } else {
      hide();
    }
    return *this;
  }

  MXObject& on(const lv_event_code_t event, const mx_event_callback_t callback);

 protected:
  lv_obj_t* lv_obj;

  lv_obj_t* get_text_obj();
};

MXObject* mx();
MXObject* mx(lv_obj_t* lv_obj);
MXObject* mx(MXScene* scene);
