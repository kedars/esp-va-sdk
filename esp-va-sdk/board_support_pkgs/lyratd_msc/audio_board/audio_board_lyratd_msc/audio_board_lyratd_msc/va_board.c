/*
*
* Copyright 2015-2018 Espressif Systems (Shanghai) PTE LTD
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*
*/

#include <string.h>
#include <esp_log.h>
#include <audio_board.h>
#include <led_msc.h>
#include <va_board.h>

#define VA_TAG "AUDIO_BOARD"

#define VA_ASSERT(a, format, b, ...) \
    if ((a) == NULL) { \
        ESP_LOGE(PLAT_TAG, format, ##__VA_ARGS__); \
        return b;\
    }

#define I2S_PORT_NUM I2S_NUM_0

bool ab_but_mute = false;

int va_board_init()
{
    int ret;
    i2s_config_t i2s_cfg = {};
    audio_board_i2s_init_default(&i2s_cfg);
    ret = i2s_driver_install(I2S_PORT_NUM, &i2s_cfg, 0, NULL);
    if (ret != ESP_OK) {
        ESP_LOGE(VA_TAG, "Error installing i2s driver for stream");
    } else {
        i2s_pin_config_t ab_i2s_pin = {0};
        audio_board_i2s_pin_config(I2S_PORT_NUM, &ab_i2s_pin);
        i2s_set_pin(I2S_PORT_NUM, &ab_i2s_pin);
    }
    ret = i2s_zero_dma_buffer(I2S_PORT_NUM);
    return ret;
}



int but_cb_reg_handlr(int ui_but_evt)
{
    return 1;
}

esp_err_t va_board_button_init()
{
    button_cfg_t *ab_button_conf = NULL;
    ab_button_conf = (button_cfg_t *)calloc(1, sizeof(button_cfg_t));
    ab_button_conf->is_adc = true;
    ab_button_conf->va_button_adc_ch_num = ADC1_CHANNEL_3;
    ab_button_conf->va_button_adc_val[VA_BUTTON_TAP_TO_TALK] = 1350;
    ab_button_conf->va_button_adc_val[VA_BUTTON_VOLUME_UP] = 2900;
    ab_button_conf->va_button_adc_val[VA_BUTTON_VOLUME_DOWN] = 2300;
    ab_button_conf->va_button_adc_val[VA_BUTTON_VAL_IDLE] = 3080;
    ab_button_conf->va_button_adc_val[VA_BUTTON_MIC_MUTE] = 1850;
    ab_button_conf->va_button_adc_val[VA_BUTTON_FACTORY_RST] = -1;
    ab_button_conf->va_button_adc_val[VA_BUTTON_CUSTOM_1] = -1;
    ab_button_conf->va_button_adc_val[VA_BUTTON_CUSTOM_2] = -1;
    ab_button_conf->tolerance = 100;
    va_button_init(ab_button_conf, but_cb_reg_handlr);
//    ab_button_gpio_init();
    return ESP_OK;
}

esp_err_t is31fl3216_init();

esp_err_t va_board_led_init()
{
    va_led_config_t *ab_led_conf = NULL;
    led_msc_pattern_init(&ab_led_conf);
    is31fl3216_init();
    va_led_init((va_led_config_t *)ab_led_conf);
    return ESP_OK;
}
