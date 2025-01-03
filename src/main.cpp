#include <Arduino.h>
#include <AsyncHTTPRequest_Generic.h>
#include <HTTPClient.h>
#include <lvgl.h>
#include <mx.h>

#include "audio/audio.h"
#include "setup/lv_setup.h"
// #include "wifi/wifi_connection.h"

AsyncHTTPRequest httpRequest;

void lv_init_ui() {
  mx()->button("Record", FONT_SIZE_4XL)
      .size_percent(50)
      .center()
      .rounded_full();
}

void setup() {
  Serial.begin(115200);

  Audio.begin();
  Audio.playSystemSound(SYSTEM_SOUND_WELCOME);

  Display.begin();
  Display.rotate(180);

  // WiFiConnection.begin();
  // WiFiConnection.connect();

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

    // Serial.print("WiFi IP: ");
    // Serial.println(WiFi.localIP());

    lastPrintTime = millis();
  }
}

void keepLVUpdate() {
  lv_timer_handler();
  delay(5);
}

// void keepWiFiConnected() {
//   if (!WiFiConnection.isConnected()) {
//     WiFiConnection.connect();
//   }
// }

void loop() {
  keepSerialAlive();
  keepLVUpdate();
  // keepWiFiConnected();
}
