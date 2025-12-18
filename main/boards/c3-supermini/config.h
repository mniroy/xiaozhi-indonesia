#ifndef _BOARD_CONFIG_H_
#define _BOARD_CONFIG_H_

#include <driver/gpio.h>

/**
 * DASAI XIAOZHI V0.01 - C3 Super Mini
 *
 * Components:
 * - ESP32-C3 Super Mini
 * - INMP441 I2S microphone
 * - MAX98357A I2S amplifier
 * - SSD1306 0.96" OLED (I2C)
 * - TTP223 touch buttons (A and B)
 * - TP4056 battery charger + 3.7V LiPo
 */

// Audio sample rates
#define AUDIO_INPUT_SAMPLE_RATE 24000
#define AUDIO_OUTPUT_SAMPLE_RATE 24000

// I2S pins for INMP441 microphone (input)
#define AUDIO_I2S_MIC_GPIO_SCK GPIO_NUM_2 // SCK/BCLK
#define AUDIO_I2S_MIC_GPIO_WS GPIO_NUM_3  // WS/LRCK
#define AUDIO_I2S_MIC_GPIO_DIN GPIO_NUM_4 // SD/DOUT from mic

// I2S pins for MAX98357A speaker (output)
#define AUDIO_I2S_SPK_GPIO_BCLK GPIO_NUM_5 // BCLK
#define AUDIO_I2S_SPK_GPIO_LRCK GPIO_NUM_6 // LRC
#define AUDIO_I2S_SPK_GPIO_DOUT GPIO_NUM_7 // DIN to speaker

// Use simplex mode (separate I2S for mic and speaker)
#define AUDIO_I2S_METHOD_SIMPLEX

// I2C pins for OLED display
#define DISPLAY_SDA_PIN GPIO_NUM_8
#define DISPLAY_SCL_PIN GPIO_NUM_10

// OLED Display configuration (SSD1306 0.96")
#define DISPLAY_WIDTH 128
#define DISPLAY_HEIGHT 64
#define DISPLAY_MIRROR_X true
#define DISPLAY_MIRROR_Y true

// LED (built-in on C3 Super Mini)
#define BUILTIN_LED_GPIO GPIO_NUM_21

// Buttons
#define BOOT_BUTTON_GPIO GPIO_NUM_9    // Boot button
#define TOUCH_BUTTON_A_GPIO GPIO_NUM_0 // TTP223-A
#define TOUCH_BUTTON_B_GPIO GPIO_NUM_1 // TTP223-B

#endif // _BOARD_CONFIG_H_
