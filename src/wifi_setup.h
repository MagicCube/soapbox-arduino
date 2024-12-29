#pragma once

#include <WiFi.h>

void setupWiFi() {
  // Connect to WiFi AP
  WiFi.mode(WIFI_STA);
  WiFi.begin("Henry's iPhone 14 Pro", "13913954971");
  while (WiFi.status() != WL_CONNECTED) {
    delay(200);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}
