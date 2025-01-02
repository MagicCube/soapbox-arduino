#include "sd_mmc_driver.h"

void init_sd_mmc() {
  SD_MMC.setPins(SD_MMC_CLK_PIN, SD_MMC_CMD_PIN, SD_MMC_D0_PIN, SD_MMC_D1_PIN,
                 SD_MMC_D2_PIN, SD_MMC_D3_PIN);
  if (!SD_MMC.begin("/sdcard")) {
    Serial.println("SD Card Mount Failed");
    return;
  }
}
