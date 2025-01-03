#pragma once

#include <mx.h>

#include "audio/audio.h"
#include "audio/audio_recorder.h"
#include "wifi/wifi_connection.h"

LV_IMAGE_DECLARE(microphone);

#define BUTTON_COLOR rgb(0xFF2C55)
#define BG_COLOR rgb(0x000000)
// #define BG_COLOR rgb(0x522069)

static lv_style_t bigRingPressedStyle;
static lv_style_t midRingPressedStyle;

class MainScene : public MXScene {
 protected:
  MXObject* speakButton;
  MXObject* bigRing;
  MXObject* midRing;

  AudioRecorder* audioRecorder;

  inline void onInit() override {
    MXScene::onInit();

    audioRecorder = new AudioRecorder();
    audioRecorder->begin();

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
                         Audio.playSystemSound(SYSTEM_SOUND_HIGHER_BEEP);
                         audioRecorder->startRecording();
                       })
                       .onReleased([this](MXEvent* e) {
                         bigRing->remove_style(&bigRingPressedStyle);
                         bigRing->bg_opacity(0.1);
                         midRing->remove_style(&midRingPressedStyle);
                         midRing->bg_opacity(0.1);
                         Audio.playSystemSound(SYSTEM_SOUND_LOWER_BEEP);
                         audioRecorder->stopRecording();
                         audioRecorder->play();
                         Audio.playSystemSound(SYSTEM_SOUND_LOWER_BEEP);
                       });
    speakButton->image(&microphone).center(0).clickable(false);

    init_pressed_style(&bigRingPressedStyle, 40);
    init_pressed_style(&midRingPressedStyle, 16);
  }

  inline void init_pressed_style(lv_style_t* style, int32_t size) {
    lv_style_init(style);
    lv_style_set_transform_width(style, size);
    lv_style_set_transform_height(style, size);
  }

  inline void onUpdate() {
    MXScene::onUpdate();
    audioRecorder->update();
  }

  inline void dispose() override {
    MXScene::dispose();

    delete bigRing;
    bigRing = nullptr;
    delete midRing;
    midRing = nullptr;
    delete speakButton;
    speakButton = nullptr;
    delete audioRecorder;
    audioRecorder = nullptr;
  }
};
