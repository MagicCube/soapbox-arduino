#include <Arduino.h>
#include <AsyncHTTPRequest_Generic.h>
#include <HTTPClient.h>
#include <lvgl.h>
#include <mx.h>

#include "audio/audio.h"
#include "setup/lv_setup.h"
#include "wifi/wifi_connection.h"

// Scenes
#include "ui/scenes/WiFiConnectionScene.h"

WiFiConnectionScene wifiConnectionScene;

void lv_init_ui() {
  wifiConnectionScene.begin();
  wifiConnectionScene.show(LV_SCR_LOAD_ANIM_NONE);
}

void setup() {
  Serial.begin(115200);

  Audio.begin();
  Audio.playSystemSound(SYSTEM_SOUND_WELCOME);

  Display.begin();
  Display.rotate(180);

  lv_setup();
  lv_init_ui();

  WiFiConnection.begin();
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

void keepLVUpdate() {
  lv_timer_handler();
  delay(5);
}

void loop() {
  keepSerialAlive();
  keepLVUpdate();

  if (MXScene::activeScene()) {
    MXScene::activeScene()->update();
  }
}
