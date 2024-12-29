#include <Arduino.h>
#include <lvgl.h>

#include "lv_setup.h"

void lv_init_ui() {
  // Add a button labeled 'Record' in the center of the screen. The size is fit
  // to the content.
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

void keepLVUpdate() {
  lv_timer_handler();
  delay(5);
}

void loop() {
  keepSerialAlive();
  keepLVUpdate();
}
