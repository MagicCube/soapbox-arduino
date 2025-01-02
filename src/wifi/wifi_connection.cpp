#include "wifi_connection.h"

#include <WiFi.h>
#include <WiFiMulti.h>

WiFiMulti wifiMulti;
WiFiConnectionClass WiFiConnection;

bool WiFiConnectionClass::isConnected() {
  return WiFi.status() == WL_CONNECTED;
}

void WiFiConnectionClass::begin() {
  WiFi.mode(WIFI_STA);
  wifiMulti.addAP("Henry's iPhone 14 Pro", "13913954971");
  wifiMulti.addAP("Henry's Living Room 2.4GHz", "13913954971");
}

void WiFiConnectionClass::connect() { wifiMulti.run(10 * 60 * 1000); }
