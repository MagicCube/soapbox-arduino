#pragma once

#include <Arduino.h>
#include <SD_MMC.h>

#include "device_conf.h"

void init_sd_mmc();

void list_files_in_sd_mmc(const char *path = "/");
