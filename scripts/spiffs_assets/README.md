# SPIFFS Assets Builder Script

This script is used to build the SPIFFS assets partition for the ESP32 project, packaging various resource files into a format that can be used on the device.

## Features

- Processes WakeNet Models
- Integrates text font files
- Processes emoji image collections
- Automatically generates resource index files
- Packages into the final `assets.bin` file

## Dependencies

- Python 3.x
- Relevant resource files

## Usage

### Basic Syntax

```bash
python scripts/spiffs_assets/spiffs_assets.py --wakenet_model [model_dir] --text_font [font_file] --emoji_collection [emoji_dir]
```

### Parameters

| Parameter | Type | Required | Description |
| :--- | :--- | :--- | :--- |
| `--wakenet_model` | Directory Path | No | Path to the WakeNet model directory |
| `--text_font` | File Path | No | Path to the text font file |
| `--emoji_collection` | Directory Path | No | Path to the emoji image collection directory |

### Examples

# Full parameter example
```bash
python scripts/spiffs_assets/spiffs_assets.py --wakenet_model main/assets/wake_word_model --text_font main/assets/fonts/PuHuiTi_Basic_20_4.bin --emoji_collection main/assets/emojis
```

# Process font files only
```bash
python scripts/spiffs_assets/spiffs_assets.py --text_font main/assets/fonts/PuHuiTi_Basic_20_4.bin
```

# Process emojis only
```bash
python scripts/spiffs_assets/spiffs_assets.py --emoji_collection main/assets/emojis
```

## Workflow

1.  **Create Build Directory Structure**
    - `build/` - Main build directory
    - `build/assets/` - Resource file directory
    - `build/output/` - Output file directory

2.  **Process WakeNet Model**
    - Copies model files to the build directory
    - Uses `pack_model.py` to generate `srmodels.bin`
    - Copies the generated model file to the resource directory

3.  **Process Text Font**
    - Copies font file to the resource directory
    - Supports `.bin` format font files

4.  **Process Emoji Collection**
    - Scans image files in the specified directory
    - Supports `.png` and `.gif` formats
    - Automatically generates emoji index

5.  **Generate Configuration Files**
    - `index.json` - Resource index file
    - `config.json` - Build configuration file

6.  **Package Final Assets**
    - Uses `spiffs_assets_gen.py` to generate `assets.bin`
    - Copies to the build root directory

## Output Files

After the build is complete, the following files will be generated in the `build/` directory:

- `assets/` - All resource files
- `assets.bin` - Final SPIFFS resource file
- `config.json` - Build configuration
- `output/` - Intermediate output files

## Supported Resource Formats

- **Model Files**: `.bin` (processed via pack_model.py)
- **Font Files**: `.bin`
- **Image Files**: `.png`, `.gif`
