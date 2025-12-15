# Xiaozhi Indonesia

An ESP32-based AI Chatbot with voice interaction capabilities.

## Features

### Core Features
- **Voice Interaction**: Streaming ASR + LLM + TTS architecture for natural conversation
- **Wi-Fi Connectivity**: Connect to the internet via Wi-Fi
- **Offline Voice Wake-up**: Uses [ESP-SR](https://github.com/espressif/esp-sr) for local wake word detection
- **Audio Codec**: OPUS audio codec for efficient audio transmission
- **Multi-language Support**: English and Indonesian language options

### Display Support
- **OLED Displays**: SSD1306 (128x32, 128x64), SH1106 (128x64)
- **LCD Displays**: Various ST7789, ST7735, ST7796, ILI9341, GC9A01 displays
- **Emoji Display**: Animated emoji expressions

### Communication Protocols
- [WebSocket Protocol](docs/websocket.md)
- MQTT + UDP hybrid protocol

### Camera Support (Optional)
- Camera integration for ESP32-S3 boards with LCD display

### Board Support
- **Bread Compact WiFi**: Basic WiFi board with OLED display -> Renamed to **ESP32-S3**
- **Bread Compact WiFi + Camera**: WiFi board with LCD display and camera support -> Renamed to **ESP32-S3 Camera**

---

## Getting Started

This guide will walk you through setting up the development environment from scratch.

### Prerequisites

Before you begin, ensure you have:
- A computer running Windows, macOS, or Linux
- An ESP32-S3 development board with PSRAM
- USB cable for connecting the board
- Basic knowledge of terminal/command line usage

---

## Step 1: Install Visual Studio Code

### Download VS Code

1. Go to [https://code.visualstudio.com/](https://code.visualstudio.com/)
2. Download the installer for your operating system
3. Run the installer and follow the installation wizard
4. Launch VS Code after installation

---

## Step 2: Install ESP-IDF Extension

### Install the Extension

1. Open VS Code
2. Click on the **Extensions** icon in the left sidebar (or press `Ctrl+Shift+X`)
3. Search for **"ESP-IDF"**
4. Find **"Espressif IDF"** by Espressif Systems
5. Click **Install**

### Configure ESP-IDF

1. After installation, press `Ctrl+Shift+P` to open the Command Palette
2. Type **"ESP-IDF: Configure ESP-IDF Extension"** and select it
3. Choose **"Express"** for the easiest setup
4. Select ESP-IDF version **5.4 or above** (required for this project)
5. Choose the installation directory (default is recommended)
6. Click **Install** and wait for the download and installation to complete

> **Note**: The installation may take 10-30 minutes depending on your internet speed.

---

## Step 3: Clone the Project

### Using Git Command Line

1. Open a terminal (Command Prompt, PowerShell, or Terminal)
2. Navigate to your desired project directory:
   ```bash
   cd /path/to/your/projects
   ```
3. Clone the repository:
   ```bash
   git clone https://github.com/royyanwicaksono/xiaozhi-indonesia.git
   ```
4. Enter the project directory:
   ```bash
   cd xiaozhi-indonesia
   ```

### Using VS Code

1. Press `Ctrl+Shift+P` to open the Command Palette
2. Type **"Git: Clone"** and select it
3. Enter the repository URL: `https://github.com/royyanwicaksono/xiaozhi-indonesia.git`
4. Select a folder to clone into
5. Click **Open** when prompted to open the cloned repository

---

## Step 4: Open the Project in VS Code

1. In VS Code, go to **File > Open Folder**
2. Navigate to and select the `xiaozhi-indonesia` folder
3. Click **Select Folder** to open the project
4. Wait for VS Code to load the project and ESP-IDF extension to initialize

---

## Step 5: Set Target Device

1. Press `Ctrl+Shift+P` to open the Command Palette
2. Type **"ESP-IDF: Set Espressif Device Target"** and select it
3. Choose your target chip:
   - **ESP32-S3** (recommended for full features including wake word)

---

## Step 6: Configure with Menuconfig

### Open Menuconfig

1. Press `Ctrl+Shift+P` to open the Command Palette
2. Type **"ESP-IDF: SDK Configuration Editor (Menuconfig)"** and select it
3. Wait for the configuration editor to open in a new tab

### Configure Xiaozhi Settings

Navigate to **Xiaozhi Assistant** in the menu and configure the following:

#### Board Type
- Select your board:
  - **ESP32-S3 Board**: For basic setup with OLED display
  - **ESP32-S3 Camera Board**: For setup with LCD and camera

#### Display Settings
- For **ESP32-S3 Board**: Select your OLED type (SSD1306 128x32, SSD1306 128x64, or SH1106 128x64)
- For **ESP32-S3 Camera Board**: Select your LCD type

#### Language
- Select **Indonesian** or **English** as the default language

#### Wake Word (Optional)
- **Disabled**: No wake word, use button to activate
- **Wakenet model with AFE**: Enable voice wake word detection (requires ESP32-S3 with PSRAM)
- **Multinet model (Custom Wake Word)**: Use a custom wake word

#### Other Options
- **Flash Assets**: Choose whether to flash default assets
- **Audio Noise Reduction**: Enable for better audio quality (ESP32-S3 with PSRAM)

### Save Configuration

1. After making your changes, click **Save** at the top of the configuration editor
2. Close the Menuconfig tab

---

## Step 7: Build the Project

### Using VS Code

1. Press `Ctrl+Shift+P` to open the Command Palette
2. Type **"ESP-IDF: Build your Project"** and select it
3. Wait for the build to complete (this may take several minutes on first build)

### Using Terminal

Alternatively, you can build using the terminal:
```bash
idf.py build
```

> **Note**: The first build will take longer as it downloads dependencies and compiles all components.

---

## Step 8: Flash the Firmware

### Connect Your Device

1. Connect your ESP32 board to your computer via USB
2. Check which COM port is assigned (Device Manager on Windows, or `/dev/tty*` on Linux/macOS)

### Flash Using VS Code

1. Press `Ctrl+Shift+P` to open the Command Palette
2. Type **"ESP-IDF: Select Port to Use"** and select your COM port
3. Type **"ESP-IDF: Flash your Project"** and select it
4. Wait for the flashing to complete

### Flash Using Terminal

```bash
idf.py -p COMX flash
```
Replace `COMX` with your actual COM port (e.g., `COM3` on Windows or `/dev/ttyUSB0` on Linux).

---

## Step 9: Monitor Serial Output

### Using VS Code

1. Press `Ctrl+Shift+P` to open the Command Palette
2. Type **"ESP-IDF: Monitor Device"** and select it

### Using Terminal

```bash
idf.py -p COMX monitor
```

### Exit Monitor

Press `Ctrl+]` to exit the monitor.

---

## Quick Commands Reference

| Action | VS Code Command Palette | Terminal Command |
|--------|------------------------|------------------|
| Set Target | ESP-IDF: Set Espressif Device Target | `idf.py set-target esp32s3` |
| Menuconfig | ESP-IDF: SDK Configuration Editor | `idf.py menuconfig` |
| Build | ESP-IDF: Build your Project | `idf.py build` |
| Flash | ESP-IDF: Flash your Project | `idf.py -p COMX flash` |
| Monitor | ESP-IDF: Monitor Device | `idf.py -p COMX monitor` |
| Full Flash | - | `idf.py -p COMX flash monitor` |
| Clean | ESP-IDF: Full Clean | `idf.py fullclean` |

---

## Troubleshooting

### Build Errors

1. **Missing ESP-IDF**: Ensure ESP-IDF 5.4+ is properly installed
2. **Python errors**: Check that Python is in your PATH
3. **Submodule issues**: Run `git submodule update --init --recursive`

### Flash Errors

1. **Port not found**: Check USB connection and drivers
2. **Permission denied (Linux)**: Add user to `dialout` group: `sudo usermod -a -G dialout $USER`
3. **Boot mode**: Hold the BOOT button while pressing RESET, then release

### Runtime Issues

1. **No audio**: Check microphone and speaker connections
2. **Wi-Fi not connecting**: Verify SSID and password in configuration
3. **Wake word not working**: Ensure ESP32-S3 with PSRAM is used

---

## Hardware Wiring

### ESP32-S3 (Basic OLED Setup)

| Periperhal | Pin Name | GPIO |
|------------|----------|------|
| **Audio (Mic)** | WS | 4 |
| | SCK | 5 |
| | DIN | 6 |
| **Audio (Speaker)** | DOUT | 7 |
| | BCLK | 15 |
| | LRCK | 16 |
| **Display (OLED)** | SDA | 41 |
| | SCL | 42 |
| **Controls** | Built-in LED | 48 |
| | Boot Button | 0 |
| | Touch Button | 47 |
| | Vol+ | 40 |
| | Vol- | 39 |

### ESP32-S3 Camera

| Periperhal | Pin Name | GPIO |
|------------|----------|------|
| **Audio (Mic)** | WS | 1 |
| | SCK | 2 |
| | DIN | 42 |
| **Audio (Speaker)** | DOUT | 39 |
| | BCLK | 40 |
| | LRCK | 41 |
| **Display (LCD)** | Backlight | 38 |
| | MOSI | 20 |
| | CLK | 19 |
| | DC | 47 |
| | RST | 21 |
| | CS | 45 |
| **Camera** | D0-D7 | 11, 9, 8, 10, 12, 18, 17, 16 |
| | XCLK | 15 |
| | PCLK | 13 |
| | VSYNC | 6 |
| | HREF | 7 |
| | SDA | 4 |
| | SCL | 5 |
| **Controls** | Built-in LED | 48 |
| | Boot Button | 0 |

---

## License

This project is released under the MIT License. See [LICENSE](LICENSE) for details.
