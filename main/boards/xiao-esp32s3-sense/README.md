# XIAO ESP32-S3 Sense Board

This board configuration is for the [Seeed Studio XIAO ESP32-S3 Sense](https://www.seeedstudio.com/XIAO-ESP32S3-Sense-p-5639.html).

## Features

- **Built-in OV2640 Camera** (on Sense expansion board)
- **Built-in PDM Microphone** (on Sense expansion board)
- **8MB PSRAM** for AI processing
- **8MB Flash** storage
- **WiFi & BLE** connectivity

## Hardware Requirements

- XIAO ESP32-S3 Sense (with Sense expansion board attached)
- External I2S Speaker/DAC module
- External SPI LCD Display (ST7789, ILI9341, GC9A01, etc.)

## Pin Configuration

### PDM Microphone (Built-in)
| Function | GPIO |
|----------|------|
| CLK | 42 |
| DATA | 41 |

### Camera (Built-in OV2640)
| Function | GPIO |
|----------|------|
| D0-D7 | 15, 17, 18, 16, 14, 12, 11, 48 |
| XCLK | 10 |
| PCLK | 13 |
| VSYNC | 38 |
| HREF | 47 |
| SDA | 40 |
| SCL | 39 |

### External I2S Speaker (User Configurable)
| Function | GPIO |
|----------|------|
| BCLK | 7 |
| LRCK | 44 |
| DOUT | 43 |

### External SPI Display (User Configurable)
| Function | GPIO |
|----------|------|
| MOSI | 9 |
| CLK | 8 |
| DC | 4 |
| RST | 5 |
| CS | 3 |

### Controls
| Function | GPIO |
|----------|------|
| Built-in LED | 21 |
| Boot Button | 0 |

## Notes

- The Sense expansion board must be attached for camera and microphone functionality.
- External I2S speaker and SPI display modules need to be connected separately.
- The default pin assignments for speaker and display can be modified in `config.h`.
