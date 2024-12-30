#include <Arduino.h>
#include <HTTPClient.h>
#include <lvgl.h>

#include "setup/lv_setup.h"
#include "setup/wifi_setup.h"
#include "sound/sound.h"

void lv_init_ui() {
  lv_obj_t *btn = lv_btn_create(lv_scr_act());
  lv_obj_set_size(btn, Display.width() / 2, Display.height() / 2);
  lv_obj_set_style_radius(btn, LV_RADIUS_CIRCLE, LV_PART_MAIN);
  lv_obj_align(btn, LV_ALIGN_CENTER, 0, 0);
  lv_obj_t *label = lv_label_create(btn);
  lv_label_set_text(label, "Start");
  lv_obj_set_style_text_font(label, &lv_font_montserrat_42, LV_PART_MAIN);
  lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
}

void setup() {
  Serial.begin(115200);
  Display.begin();
  Display.rotate(180);
  Sound.begin();
  lv_setup();

  Sound.playSystemSound(SYSTEM_SOUND_WELCOME);

  lv_init_ui();

  setupWiFi();

  HTTPClient http;
  http.begin("https://soap.henry1943.top/speech.pcm");
  http.addHeader("Host", "soap.henry1943.top");
  int httpCode = http.GET();
  if (httpCode == HTTP_CODE_OK) {
    WiFiClient *stream = http.getStreamPtr();
    uint8_t buffer[1024];

    while (http.connected()) {
      size_t size = stream->available();
      if (size) {
        int c = stream->readBytes(
            buffer, ((size > sizeof(buffer)) ? sizeof(buffer) : size));
        // 处理读取的数据
        Serial.printf("Read %d bytes\n", c);
        Sound.write((int16_t *)buffer, c);
      }
      delay(1);  // 避免 watchdog timer 触发
    }
  } else {
    Serial.printf("GET request failed, error: %s\n",
                  http.errorToString(httpCode).c_str());
  }
}

time_t lastPrintTime = 0;
void keepSerialAlive() {
  if (millis() - lastPrintTime > 5 * 1000) {
    // Serial.print(".");
    // Print free memory
    Serial.print("Free memory: ");
    Serial.println(esp_get_free_heap_size());

    // Serial.print("WiFi status: ");
    // Serial.println(WiFi.status());

    // Serial.print("WiFi IP: ");
    // Serial.println(WiFi.localIP());

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
}
