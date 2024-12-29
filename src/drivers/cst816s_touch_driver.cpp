#include "cst816s_touch_driver.h"

#include "device_conf.h"

ESP_PanelTouch_CST816S* cst816s_init_touch() {
  ESP_PanelBus_I2C* bus =
      new ESP_PanelBus_I2C(TOUCH_PIN_NUM_I2C_SCL, TOUCH_PIN_NUM_I2C_SDA,
                           ESP_LCD_TOUCH_IO_I2C_CST816S_CONFIG());
  bus->configI2cFreqHz(400000);
  bus->begin();

  auto touch =
      new ESP_PanelTouch_CST816S(bus, DISPLAY_RES_WIDTH, DISPLAY_RES_HEIGHT,
                                 TOUCH_PIN_NUM_RST, TOUCH_PIN_NUM_INT);
  touch->init();
  touch->begin();
  return touch;
}
