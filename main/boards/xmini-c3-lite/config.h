#ifndef _BOARD_CONFIG_H_
#define _BOARD_CONFIG_H_

#include <driver/gpio.h>

// Audio sample rates
#define AUDIO_INPUT_SAMPLE_RATE 24000
#define AUDIO_OUTPUT_SAMPLE_RATE 24000

// I2S pins for INMP441 microphone (input)
#define AUDIO_I2S_MIC_GPIO_SCK GPIO_NUM_4 // BCLK
#define AUDIO_I2S_MIC_GPIO_WS GPIO_NUM_5  // LRCK/WS
#define AUDIO_I2S_MIC_GPIO_DIN GPIO_NUM_6 // SD/DOUT from mic

// I2S pins for MAX98357A speaker (output)
#define AUDIO_I2S_SPK_GPIO_BCLK GPIO_NUM_4 // BCLK (shared with mic)
#define AUDIO_I2S_SPK_GPIO_LRCK GPIO_NUM_5 // LRC (shared with mic)
#define AUDIO_I2S_SPK_GPIO_DOUT GPIO_NUM_7 // DIN to speaker

// Use simplex mode (separate I2S for mic and speaker)
#define AUDIO_I2S_METHOD_SIMPLEX

// LED and button
#define BUILTIN_LED_GPIO GPIO_NUM_2
#define BOOT_BUTTON_GPIO GPIO_NUM_9

#endif // _BOARD_CONFIG_H_
