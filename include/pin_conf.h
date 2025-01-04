#pragma once

#define DISPLAY_BACKLIGHT_PIN 15

#define TFT_RST 47
#define TFT_CS 10
#define TFT_SCK 9
#define TFT_SDA0 11
#define TFT_SDA1 12
#define TFT_SDA2 13
#define TFT_SDA3 14

#define TOUCH_PIN_NUM_I2C_SCL 8
#define TOUCH_PIN_NUM_I2C_SDA 7
#define TOUCH_PIN_NUM_INT 41
#define TOUCH_PIN_NUM_RST 40

#define SD_MMC_D0 2
#define SD_MMC_D1 1
#define SD_MMC_D2 6
#define SD_MMC_D3 5
#define SD_MMC_CLK 3
#define SD_MMC_CMD 4

#define SPEAKER_I2S_MCK_IO -1  // MCK
#define SPEAKER_I2S_BCK_IO 18  // BCK
#define SPEAKER_I2S_WS_IO 16   // LCK
#define SPEAKER_I2S_DO_IO 17   // DIN
#define SPEAKER_MUTE_PIN 48    // 低电平静音

#define MIC_I2S_WS 45
#define MIC_I2S_SD 46
#define MIC_I2S_SCK 42
