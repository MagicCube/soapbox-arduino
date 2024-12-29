#include <Arduino.h>

void setup() { Serial.begin(115200); }

time_t lastPrintTime = 0;
void keepSerialAlive() {
  if (millis() - lastPrintTime > 5 * 1000) {
    Serial.print(".");
    lastPrintTime = millis();
  }
}

void loop() { keepSerialAlive(); }
