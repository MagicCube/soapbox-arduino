#pragma once

#include <Arduino.h>
#include <ESP_IOExpander.h>
#include <ESP_Panel_Library.h>

#include "device_conf.h"

ESP_PanelLcd_ST77916* st77916_init_lcd();
ESP_PanelBacklight* st77916_init_backlight();
