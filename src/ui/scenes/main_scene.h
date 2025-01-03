#pragma once

#include <mx.h>

#include "wifi/wifi_connection.h"

LV_IMAGE_DECLARE(microphone);

class MainScene : public MXScene {
 protected:
  MXObject* speakButton;

  inline void onInit() override {
    MXScene::onInit();
    root()->bg(rgb(0x522069)).scrollable(false);
    speakButton =
        &root()
             ->button()
             .size(256)
             .center(0, 140)
             .bg(rgb(0xFF2C55))
             .rounded_full()
             .onClick([](MXEvent* e) { Serial.println("Clicked"); })
             .onPressed([](MXEvent* e) { Serial.println("Pressed"); })
             .onReleased([](MXEvent* e) { Serial.println("Released"); });
    speakButton->object()
        .size(200)
        .center()
        .bg_white(0.1)
        .rounded_full()
        .clickable(false);
    speakButton->object()
        .size(144)
        .center()
        .bg_white(0.1)
        .rounded_full()
        .clickable(false);
    speakButton->image(&microphone).center(0, -6).clickable(false);
  }

  inline void dispose() override { MXScene::dispose(); }
};
