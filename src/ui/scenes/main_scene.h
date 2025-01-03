#pragma once

#include <mx.h>

#include "wifi/wifi_connection.h"

LV_IMAGE_DECLARE(microphone);

#define BUTTON_COLOR rgb(0xFF2C55)
#define BG_COLOR rgb(0x522069)

static lv_style_t bigRingPressedStyle;
static lv_style_t midRingPressedStyle;

class MainScene : public MXScene {
 protected:
  MXObject* speakButton;
  MXObject* bigRing;
  MXObject* midRing;

  inline void onInit() override {
    MXScene::onInit();
    root()->bg(BG_COLOR).scrollable(false);

    bigRing = &root()
                   ->object()
                   .size(256)
                   .center(0, 96)
                   .bg_white(0.1)
                   .rounded_full()
                   .clickable(false);
    midRing = &bigRing->object()
                   .size(200)
                   .center()
                   .bg_white(0.1)
                   .rounded_full()
                   .clickable(false);
    speakButton = &bigRing->button()
                       .size(144)
                       .center()
                       .bg(BUTTON_COLOR)
                       .rounded_full()
                       .onClick([](MXEvent* e) { Serial.println("Clicked"); })
                       .onPressed([this](MXEvent* e) {
                         bigRing->add_style(&bigRingPressedStyle);
                         bigRing->bg_opacity(0.05);
                         midRing->add_style(&midRingPressedStyle);
                         midRing->bg_opacity(0.05);
                       })
                       .onReleased([this](MXEvent* e) {
                         bigRing->remove_style(&bigRingPressedStyle);
                         bigRing->bg_opacity(0.1);
                         midRing->remove_style(&midRingPressedStyle);
                         midRing->bg_opacity(0.1);
                       });
    speakButton->image(&microphone).center(0).clickable(false);

    // Big ring pressed style
    init_style(&bigRingPressedStyle, 40);
    init_style(&midRingPressedStyle, 16);
  }

  inline void init_style(lv_style_t* style, int32_t size) {
    lv_style_init(style);
    lv_style_set_transform_width(style, size);
    lv_style_set_transform_height(style, size);
  }

  inline void dispose() override { MXScene::dispose(); }
};