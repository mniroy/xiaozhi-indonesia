Hardware based on ESP32S3CAM development board, code modified from esp32-s3-lcd.
The camera used is OV2640.
Note: Because the camera requires many IO pins, it occupies the USB pins 19 and 20 of the ESP32S3.
For wiring connections, please refer to the pin definitions in the `config.h` file.

# Build and Configuration Commands

**Set build target to ESP32S3:**

```bash
idf.py set-target esp32s3
```

**Open menuconfig:**

```bash
idf.py menuconfig
```

**Select Board:**

```bash
Xiaozhi Assistant -> Board Type -> ESP32-S3 Camera Board
```

**Configure Camera Sensor:**

> **Note:** Confirm the camera sensor model and ensure it is supported by `esp_cam_sensor`. The current board uses OV2640, which is supported.

Enable support for the corresponding model in menuconfig using the following steps:

1. **Navigate to Sensor Configuration:**
   ```
   (Top) → Component config → Espressif Camera Sensors Configurations → Camera Sensor Configuration → Select and Set Camera Sensor
   ```

2. **Select Sensor Model:**
   - Select the required sensor model (OV2640)

3. **Configure Sensor Parameters:**
   - Press → to enter sensor detailed settings
   - Enable **Auto detect**
   - Recommended: Set **default output format** to **YUV422** and choose an appropriate resolution
   - (Currently supports YUV422 and RGB565; YUV422 is more memory efficient)

**Build and Flash:**

```bash
idf.py build flash
```