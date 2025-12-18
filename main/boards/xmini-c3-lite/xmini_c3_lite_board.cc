/**
 * XMini-C3 Lite Board - Walkie-Talkie Style
 *
 * Simple board without display using:
 * - INMP441 I2S microphone
 * - MAX98357A I2S amplifier
 * - Single LED for status indication
 * - Boot button for push-to-talk
 */

#include "application.h"
#include "button.h"
#include "codecs/no_audio_codec.h"
#include "config.h"
#include "display/no_display.h"
#include "led/single_led.h"
#include "wifi_board.h"


#include <esp_efuse.h>
#include <esp_efuse_table.h>
#include <esp_log.h>


#define TAG "XminiC3LiteBoard"

class XminiC3LiteBoard : public WifiBoard {
private:
  Button boot_button_;

  void InitializeButtons() {
    // Click: Toggle chat state or enter WiFi config
    boot_button_.OnClick([this]() {
      auto &app = Application::GetInstance();
      if (app.GetDeviceState() == kDeviceStateStarting) {
        EnterWifiConfigMode();
        return;
      }
      app.ToggleChatState();
    });

    // Press and hold: Push-to-talk (walkie-talkie style)
    boot_button_.OnPressDown(
        [this]() { Application::GetInstance().StartListening(); });

    boot_button_.OnPressUp(
        [this]() { Application::GetInstance().StopListening(); });
  }

public:
  XminiC3LiteBoard() : boot_button_(BOOT_BUTTON_GPIO) {
    InitializeButtons();

    // Use ESP32C3's VDD SPI pin as normal GPIO
    esp_efuse_write_field_bit(ESP_EFUSE_VDD_SPI_AS_GPIO);

    ESP_LOGI(TAG, "XMini-C3 Lite Board initialized (INMP441 + MAX98357A)");
  }

  virtual Led *GetLed() override {
    static SingleLed led(BUILTIN_LED_GPIO);
    return &led;
  }

  virtual Display *GetDisplay() override {
    static NoDisplay no_display;
    return &no_display;
  }

  virtual AudioCodec *GetAudioCodec() override {
    static NoAudioCodecSimplex audio_codec(
        AUDIO_INPUT_SAMPLE_RATE, AUDIO_OUTPUT_SAMPLE_RATE,
        AUDIO_I2S_SPK_GPIO_BCLK, AUDIO_I2S_SPK_GPIO_LRCK,
        AUDIO_I2S_SPK_GPIO_DOUT, AUDIO_I2S_MIC_GPIO_SCK, AUDIO_I2S_MIC_GPIO_WS,
        AUDIO_I2S_MIC_GPIO_DIN);
    return &audio_codec;
  }
};

DECLARE_BOARD(XminiC3LiteBoard);
