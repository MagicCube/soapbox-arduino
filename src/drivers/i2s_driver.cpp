#include "i2s_driver.h"

#include <Arduino.h>

#include "device_conf.h"

void i2s_init_speaker() {
  i2s_config_t i2s_config = {
      .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX),
      .sample_rate = RECORDING_SAMPLE_RATE,
      .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
      .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
      .communication_format = I2S_COMM_FORMAT_STAND_I2S,
      .intr_alloc_flags = 0,
      .dma_buf_count = 8,
      .dma_buf_len = 64,
      .use_apll = false,
      .tx_desc_auto_clear = true};

  i2s_pin_config_t pin_config = {.bck_io_num = SPEAKER_I2S_BCK_IO,
                                 .ws_io_num = SPEAKER_I2S_WS_IO,
                                 .data_out_num = SPEAKER_I2S_DO_IO,
                                 .data_in_num = I2S_PIN_NO_CHANGE};

  i2s_driver_uninstall(SPEAKER_I2S_PORT);
  i2s_driver_install(SPEAKER_I2S_PORT, &i2s_config, 0, NULL);
  i2s_set_pin(SPEAKER_I2S_PORT, &pin_config);
}

void i2s_init_mic() {
  i2s_config_t i2s_config = {
      .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX),
      .sample_rate = RECORDING_SAMPLE_RATE,
      .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
      .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
      .communication_format = I2S_COMM_FORMAT_STAND_I2S,
      .intr_alloc_flags = 0,
      .dma_buf_count = 8,
      .dma_buf_len = 64,
      .use_apll = false,
      .tx_desc_auto_clear = true};

  i2s_pin_config_t pin_config = {.bck_io_num = MIC_I2S_SCK,
                                 .ws_io_num = MIC_I2S_WS,
                                 .data_out_num = I2S_PIN_NO_CHANGE,
                                 .data_in_num = MIC_I2S_SD};

  i2s_driver_uninstall(MIC_I2S_PORT);
  i2s_driver_install(MIC_I2S_PORT, &i2s_config, 0, NULL);
  i2s_set_pin(MIC_I2S_PORT, &pin_config);
}
