#pragma once

#include <Arduino.h>
#include <ESP_IOExpander.h>
#include <ESP_Panel_Library.h>

#include "device_conf.h"

ESP_PanelTouch_CST816S* cst816s_init_touch();
