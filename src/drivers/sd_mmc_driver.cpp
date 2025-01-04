#include "sd_mmc_driver.h"

#if defined(SD_MMC_D1_PIN)
#define SD_MMC_MODE_1BIT false
#else
#define SD_MMC_MODE_1BIT true
#endif

void init_sd_mmc() {
#if defined(SD_MMC_D1_PIN)
  SD_MMC.setPins(SD_MMC_CLK_PIN, SD_MMC_CMD_PIN, SD_MMC_D0_PIN, SD_MMC_D1_PIN,
                 SD_MMC_D2_PIN, SD_MMC_D3_PIN);
#else
  SD_MMC.setPins(SD_MMC_CLK_PIN, SD_MMC_CMD_PIN, SD_MMC_D0_PIN);
#endif
  if (!SD_MMC.begin("/sdcard", SD_MMC_MODE_1BIT)) {
    Serial.println("Failed to mount SD card");
    return;
  }
  Serial.println("SD card mounted at \"/sdcard\"");
}

void list_files_in_sd_mmc(const char *path) {
  File root = SD_MMC.open(path);
  File file = root.openNextFile();
  while (file) {
    Serial.println(file.name());
    file = root.openNextFile();
  }
}
