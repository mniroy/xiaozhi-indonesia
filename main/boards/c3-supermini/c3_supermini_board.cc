/**
 * DASAI XIAOZHI V0.01 - C3 Super Mini Board
 *
 * Based on wiring diagram from xiaozhi.vn
 *
 * Hardware:
 * - ESP32-C3 Super Mini (4MB flash)
 * - INMP441 I2S microphone
 * - MAX98357A I2S amplifier + speaker
 * - SSD1306 0.96" OLED display (I2C)
 * - TTP223 touch buttons (A and B)
 * - TP4056 battery charger + 3.7V LiPo
 */

#include "application.h"
#include "assets/lang_config.h"
#include "button.h"
#include "codecs/no_audio_codec.h"
#include "config.h"
#include "display/oled_display.h"
#include "led/single_led.h"
#include "wifi_board.h"


#include <driver/i2c_master.h>
#include <esp_efuse.h>
#include <esp_efuse_table.h>
#include <esp_lcd_panel_ops.h>
#include <esp_lcd_panel_vendor.h>
#include <esp_log.h>


#define TAG "C3SuperMiniBoard"

class C3SuperMiniBoard : public WifiBoard {
private:
  i2c_master_bus_handle_t display_i2c_bus_;
  esp_lcd_panel_io_handle_t panel_io_ = nullptr;
  esp_lcd_panel_handle_t panel_ = nullptr;
  Display *display_ = nullptr;
  Button boot_button_;
  Button touch_button_a_;
  Button touch_button_b_;

  void InitializeDisplayI2c() {
    i2c_master_bus_config_t bus_config = {
        .i2c_port = I2C_NUM_0,
        .sda_io_num = DISPLAY_SDA_PIN,
        .scl_io_num = DISPLAY_SCL_PIN,
        .clk_source = I2C_CLK_SRC_DEFAULT,
        .glitch_ignore_cnt = 7,
        .intr_priority = 0,
        .trans_queue_depth = 0,
        .flags =
            {
                .enable_internal_pullup = 1,
            },
    };
    ESP_ERROR_CHECK(i2c_new_master_bus(&bus_config, &display_i2c_bus_));
    ESP_LOGI(TAG, "I2C bus initialized for display");
  }

  void InitializeSsd1306Display() {
    // SSD1306 I2C config
    esp_lcd_panel_io_i2c_config_t io_config = {
        .dev_addr = 0x3C,
        .on_color_trans_done = nullptr,
        .user_ctx = nullptr,
        .control_phase_bytes = 1,
        .dc_bit_offset = 6,
        .lcd_cmd_bits = 8,
        .lcd_param_bits = 8,
        .flags =
            {
                .dc_low_on_data = 0,
                .disable_control_phase = 0,
            },
        .scl_speed_hz = 400 * 1000,
    };

    ESP_ERROR_CHECK(
        esp_lcd_new_panel_io_i2c_v2(display_i2c_bus_, &io_config, &panel_io_));

    ESP_LOGI(TAG, "Installing SSD1306 driver");
    esp_lcd_panel_dev_config_t panel_config = {};
    panel_config.reset_gpio_num = -1;
    panel_config.bits_per_pixel = 1;

    esp_lcd_panel_ssd1306_config_t ssd1306_config = {
        .height = static_cast<uint8_t>(DISPLAY_HEIGHT),
    };
    panel_config.vendor_config = &ssd1306_config;

    ESP_ERROR_CHECK(
        esp_lcd_new_panel_ssd1306(panel_io_, &panel_config, &panel_));
    ESP_LOGI(TAG, "SSD1306 driver installed");

    ESP_ERROR_CHECK(esp_lcd_panel_reset(panel_));
    if (esp_lcd_panel_init(panel_) != ESP_OK) {
      ESP_LOGE(TAG, "Failed to initialize display");
      display_ = new NoDisplay();
      return;
    }

    ESP_LOGI(TAG, "Turning display on");
    ESP_ERROR_CHECK(esp_lcd_panel_disp_on_off(panel_, true));

    display_ = new OledDisplay(panel_io_, panel_, DISPLAY_WIDTH, DISPLAY_HEIGHT,
                               DISPLAY_MIRROR_X, DISPLAY_MIRROR_Y);
  }

  void InitializeButtons() {
    // Boot button: Click to toggle chat or enter WiFi config
    boot_button_.OnClick([this]() {
      auto &app = Application::GetInstance();
      if (app.GetDeviceState() == kDeviceStateStarting) {
        EnterWifiConfigMode();
        return;
      }
      app.ToggleChatState();
    });

    // Touch button A: Push-to-talk
    touch_button_a_.OnPressDown(
        [this]() { Application::GetInstance().StartListening(); });
    touch_button_a_.OnPressUp(
        [this]() { Application::GetInstance().StopListening(); });

    // Touch button B: Volume control
    touch_button_b_.OnClick([this]() {
      auto codec = GetAudioCodec();
      auto volume = codec->output_volume() + 10;
      if (volume > 100) {
        volume = 100;
      }
      codec->SetOutputVolume(volume);
      GetDisplay()->ShowNotification(Lang::Strings::VOLUME +
                                     std::to_string(volume));
    });

    touch_button_b_.OnLongPress([this]() {
      auto codec = GetAudioCodec();
      codec->SetOutputVolume(0);
      GetDisplay()->ShowNotification(Lang::Strings::MUTED);
    });
  }

public:
  C3SuperMiniBoard()
      : boot_button_(BOOT_BUTTON_GPIO), touch_button_a_(TOUCH_BUTTON_A_GPIO),
        touch_button_b_(TOUCH_BUTTON_B_GPIO) {

    InitializeDisplayI2c();
    InitializeSsd1306Display();
    InitializeButtons();

    // Use ESP32C3's VDD SPI pin as normal GPIO
    esp_efuse_write_field_bit(ESP_EFUSE_VDD_SPI_AS_GPIO);

    ESP_LOGI(TAG,
             "C3 Super Mini Board initialized (INMP441 + MAX98357A + SSD1306)");
  }

  virtual Led *GetLed() override {
    static SingleLed led(BUILTIN_LED_GPIO);
    return &led;
  }

  virtual Display *GetDisplay() override { return display_; }

  virtual AudioCodec *GetAudioCodec() override {
    static NoAudioCodecSimplex audio_codec(
        AUDIO_INPUT_SAMPLE_RATE, AUDIO_OUTPUT_SAMPLE_RATE,
        AUDIO_I2S_SPK_GPIO_BCLK, AUDIO_I2S_SPK_GPIO_LRCK,
        AUDIO_I2S_SPK_GPIO_DOUT, AUDIO_I2S_MIC_GPIO_SCK, AUDIO_I2S_MIC_GPIO_WS,
        AUDIO_I2S_MIC_GPIO_DIN);
    return &audio_codec;
  }
};

DECLARE_BOARD(C3SuperMiniBoard);
