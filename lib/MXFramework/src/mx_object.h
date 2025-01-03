#pragma once

#include <Arduino.h>
#include <lvgl.h>

#include "mx_event.h"
#include "mx_font.h"

inline lv_color_t mx_theme_color_primary() {
  return lv_theme_get_color_primary(lv_screen_active());
}

inline lv_color_t mx_theme_color_secondary() {
  return lv_theme_get_color_secondary(lv_screen_active());
}

class MXScene;

class MXObject {
 public:
  inline MXObject(lv_obj_t* obj = nullptr) : lv_obj(obj) {
    if (obj == nullptr) {
      lv_obj = lv_obj_create(nullptr);
    }
  }

  inline ~MXObject() {
    if (lv_obj) {
      lv_obj_del(lv_obj);
    }
  }

  inline MXObject& object(const int32_t width = -1, const int32_t height = -1) {
    lv_obj_t* lv_object = lv_obj_create(lv_obj);
    MXObject* object = new MXObject(lv_object);
    if (width >= 0) {
      object->w(width);
    }
    if (height >= 0) {
      object->h(height);
    }
    object->bg_transparent();
    object->border_none();
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
    if (text != nullptr) {
      lv_obj_t* lv_label = lv_label_create(lv_button);
      lv_obj_align(lv_label, LV_ALIGN_CENTER, 0, 0);
      button->text(text);
      button->text(fontSize);
    }
    return *button;
  }

  inline MXObject& image(const void* src = nullptr) {
    lv_obj_t* lv_image = lv_img_create(lv_obj);
    MXObject* image = new MXObject(lv_image);
    if (src != nullptr) {
      image->src(src);
    }
    return *image;
  }

  inline MXObject& src(const void* src) {
    lv_img_set_src(lv_obj, src);
    return *this;
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
  MXObject& align(const lv_align_t align, const lv_coord_t offset_x = 0,
                  const lv_coord_t offset_y = 0);
  inline MXObject& center(const lv_coord_t offset_x = 0,
                          const lv_coord_t offset_y = 0) {
    return this->align(LV_ALIGN_CENTER, offset_x, offset_y);
  }
  inline MXObject& center_x(const lv_coord_t offset_x = 0,
                            const lv_coord_t offset_y = 0) {
    return this->align(LV_ALIGN_TOP_MID, offset_x, offset_y);
  }
  inline MXObject& center_y(const lv_coord_t offset_x = 0,
                            const lv_coord_t offset_y = 0) {
    return this->align(LV_ALIGN_LEFT_MID, offset_x, offset_y);
  }

  // Border
  MXObject& border(const uint16_t size,
                   const lv_color_t color = lv_color_black(),
                   const lv_border_side_t side = LV_BORDER_SIDE_FULL);
  MXObject& border_none();

  // Background
  MXObject& bg(const lv_color_t color, const float opacity = 1);
  MXObject& bg_opacity(const float opacity);
  MXObject& bg_transparent() { return this->bg(lv_color_black(), 0); }
  MXObject& bg_primary(const float opacity = 1) {
    return this->bg(mx_theme_color_primary(), opacity);
  }
  MXObject& bg_secondary(const float opacity = 1) {
    return this->bg(mx_theme_color_secondary(), opacity);
  }
  MXObject& bg_white(const float opacity = 1) {
    return this->bg(lv_color_white(), opacity);
  }
  MXObject& bg_black(const float opacity = 1) {
    return this->bg(lv_color_black(), opacity);
  }

  // Opacity
  MXObject& opacity(const float opacity);

  // Font
  MXObject& font(const lv_font_t* font);

  // Text
  MXObject& text(const char* text);
  MXObject& text_format(const char* format, ...);

  // Text Style
  MXObject& text(const MXFontSize size);
  MXObject& text(const lv_color_t color);
  MXObject& text_primary() { return this->text(mx_theme_color_primary()); }
  MXObject& text_white() { return this->text(lv_color_white()); }
  MXObject& text_black() { return this->text(lv_color_black()); }
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

  // Style
  MXObject& add_style(const lv_style_t* style);
  MXObject& remove_style(const lv_style_t* style);

  // Flags
  MXObject& clickable(bool value);
  MXObject& scrollable(bool value);

  // Events
  MXObject& on(const lv_event_code_t event, const mx_event_callback_t callback);
  inline MXObject& onClick(const mx_event_callback_t callback) {
    return this->on(LV_EVENT_CLICKED, callback);
  }
  inline MXObject& onPressed(const mx_event_callback_t callback) {
    return this->on(LV_EVENT_PRESSED, callback);
  }
  inline MXObject& onReleased(const mx_event_callback_t callback) {
    return this->on(LV_EVENT_RELEASED, callback);
  }

 protected:
  lv_obj_t* lv_obj;

  lv_obj_t* get_text_obj();
};

MXObject* mx();
MXObject* mx(lv_obj_t* lv_obj);
MXObject* mx(MXScene* scene);
