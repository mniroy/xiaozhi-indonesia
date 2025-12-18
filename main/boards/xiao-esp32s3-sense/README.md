# XIAO ESP32-S3 Sense Board

This board configuration is for the [Seeed Studio XIAO ESP32-S3 Sense](https://www.seeedstudio.com/XIAO-ESP32S3-Sense-p-5639.html).

## Features

- **Built-in OV2640/OV3660 Camera** (on Sense expansion board)
- **Built-in PDM Microphone** (on Sense expansion board)
- **8MB PSRAM** for AI processing
- **8MB Flash** storage
- **WiFi & BLE** connectivity

## Hardware Requirements

- XIAO ESP32-S3 Sense (with Sense expansion board attached)
- MAX98357A I2S Amplifier Module
- Speaker (3W recommended)
- External SPI LCD Display (optional - ST7789, ILI9341, GC9A01, etc.)

## Pin Configuration

### PDM Microphone (Built-in)
| Function | GPIO | Pin Label |
|----------|------|-----------|
| CLK | 42 | Internal |
| DATA | 41 | Internal |

### Camera (Built-in)
| Function | GPIO |
|----------|------|
| D0-D7 | 15, 17, 18, 16, 14, 12, 11, 48 |
| XCLK | 10 |
| PCLK | 13 |
| VSYNC | 38 |
| HREF | 47 |
| SDA | 40 |
| SCL | 39 |

### MAX98357A I2S Speaker Wiring
| MAX98357A | XIAO ESP32-S3 | GPIO |
|-----------|---------------|------|
| VIN | 3.3V or 5V | - |
| GND | GND | - |
| SD | 3.3V (or floating) | - |
| GAIN | Floating (9dB) | - |
| BCLK | D4 | GPIO 5 |
| LRC | D5 | GPIO 6 |
| DIN | D6 | GPIO 43 |

> **Important:** The SD pin must be connected to 3.3V or left floating. If connected to GND, the amplifier will be in shutdown mode (no sound).

### External SPI Display (Optional)
| Function | Pin | GPIO |
|----------|-----|------|
| MOSI | D9 | 9 |
| CLK | D8 | 8 |
| DC | D7 | 7 |
| RST | D10 | 44 |
| CS | D2 | 3 |

### Controls
| Function | Pin | GPIO |
|----------|-----|------|
| Built-in LED | - | 21 |
| Boot Button | - | 0 |

---

## Build & Flash Guide

### 1. Set Target
```bash
idf.py set-target esp32s3
```

### 2. Configure with Menuconfig
```bash
idf.py menuconfig
```

Navigate and set the following options:

#### Serial flasher config
- **Flash size** → `8 MB`

#### Partition Table
- **Partition Table** → `Custom partition table CSV`
- **Custom partition CSV file** → `partitions/v2/8m.csv`

#### Xiaozhi Assistant Configuration
- **Board Type** → `XIAO ESP32-S3 Sense`
- **Language** → Select your preferred language

#### Camera Configuration (Component config → ESP Video → Camera Configuration)
- **Camera Sensor** → `OV3660` (or `OV2640` depending on your camera module)

#### Display Configuration (if not using display)
- In `Xiaozhi Assistant` → **LCD Display Type** → `No Display`

### 3. Build
```bash
idf.py build
```

### 4. Flash
```bash
idf.py -p COM<X> flash monitor
```

Replace `COM<X>` with your actual COM port (e.g., `COM3` on Windows, `/dev/ttyUSB0` on Linux).

---

## Troubleshooting

### No Sound from Speaker
1. Check SD pin on MAX98357A is connected to 3.3V (not GND)
2. Verify wiring: BCLK→D4, LRC→D5, DIN→D6
3. Check speaker is connected properly to MAX98357A output

### Camera Not Working
1. Ensure Sense expansion board is properly attached
2. Verify camera sensor type matches menuconfig setting (OV2640/OV3660)

### Flash Size Error
1. Make sure Flash size is set to 8MB in menuconfig
2. Use the correct partition table: `partitions/v2/8m.csv`

---

## Notes

- The Sense expansion board must be attached for camera and microphone functionality.
- The default pin assignments can be modified in `config.h`.
- For OV3660 camera, make sure to select it in menuconfig under Camera Configuration.
