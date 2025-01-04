#include <Arduino.h>
#include <AsyncHTTPRequest_Generic.h>
#include <HTTPClient.h>
#include <lvgl.h>
#include <mx.h>

#include "audio/audio.h"
#include "display/touch_lcd_display.h"
#include "setup/lv_setup.h"

// Scenes
#include "ui/scenes/main_scene.h"
#include "ui/scenes/voice_repeater_scene.h"
#include "ui/scenes/wifi_connection_scene.h"

MainScene mainScene;
// VoiceRepeaterScene voiceRepeaterScene;
// WiFiConnectionScene wifiConnectionScene;

void lv_init_ui() {
  // wifiConnectionScene.begin();
  // wifiConnectionScene.show(LV_SCR_LOAD_ANIM_NONE);
  mainScene.begin();
  mainScene.show();
}

void setup() {
  Serial.begin(115200);

  Audio.begin();
  Audio.playSystemSound(SYSTEM_SOUND_STARTUP);

  Display.begin();
  Display.rotate(180);

  lv_setup();
  lv_init_ui();
}

time_t lastPrintTime = 0;
void keepSerialAlive() {
  if (millis() - lastPrintTime > 5 * 1000) {
    // Serial.print(".");
    // Print free memory
    Serial.print("Free memory: ");
    Serial.println(esp_get_free_heap_size());

    lastPrintTime = millis();
  }
}

void keepUIUpdate() {
  if (MXScene::activeScene()) {
    MXScene::activeScene()->update();
  }
  // if (WiFiConnection.isConnected() &&
  //     MXScene::activeScene() == &wifiConnectionScene) {
  //   mainScene.begin();
  //   mainScene.show();
  // }
}

void keepLVUpdate() {
  lv_timer_handler();
  delay(5);
}

void loop() {
  keepSerialAlive();
  keepUIUpdate();
  keepLVUpdate();
}
