@echo off
REM Build script for all 3 boards
REM This script creates separate build directories for each board

setlocal enabledelayedexpansion

set PROJECT_DIR=%~dp0
set BUILD_OUTPUT=%PROJECT_DIR%firmware_builds

echo ========================================
echo Building firmware for all boards
echo ========================================

REM Create output directory
if not exist "%BUILD_OUTPUT%" mkdir "%BUILD_OUTPUT%"

REM Build ESP32-S3 Board (OLED)
echo.
echo [1/3] Building ESP32-S3 Board...
echo ----------------------------------------
set SDKCONFIG_DEFAULTS=%PROJECT_DIR%sdkconfig.defaults;%PROJECT_DIR%sdkconfig.defaults.esp32s3;%PROJECT_DIR%sdkconfig.board.esp32-s3
call idf.py -B build_esp32s3 set-target esp32s3
call idf.py -B build_esp32s3 -D SDKCONFIG_DEFAULTS="%SDKCONFIG_DEFAULTS%" build
if errorlevel 1 (
    echo ERROR: Build failed for ESP32-S3 Board
) else (
    copy build_esp32s3\xiaozhi-esp32.bin "%BUILD_OUTPUT%\xiaozhi-esp32-s3.bin"
    echo SUCCESS: ESP32-S3 Board firmware built
)

REM Build ESP32-S3 Camera Board (LCD)
echo.
echo [2/3] Building ESP32-S3 Camera Board...
echo ----------------------------------------
set SDKCONFIG_DEFAULTS=%PROJECT_DIR%sdkconfig.defaults;%PROJECT_DIR%sdkconfig.defaults.esp32s3;%PROJECT_DIR%sdkconfig.board.esp32-s3-cam
call idf.py -B build_esp32s3cam set-target esp32s3
call idf.py -B build_esp32s3cam -D SDKCONFIG_DEFAULTS="%SDKCONFIG_DEFAULTS%" build
if errorlevel 1 (
    echo ERROR: Build failed for ESP32-S3 Camera Board
) else (
    copy build_esp32s3cam\xiaozhi-esp32.bin "%BUILD_OUTPUT%\xiaozhi-esp32-s3-cam.bin"
    echo SUCCESS: ESP32-S3 Camera Board firmware built
)

REM Build XIAO ESP32-S3 Sense Board
echo.
echo [3/3] Building XIAO ESP32-S3 Sense Board...
echo ----------------------------------------
set SDKCONFIG_DEFAULTS=%PROJECT_DIR%sdkconfig.defaults;%PROJECT_DIR%sdkconfig.defaults.esp32s3;%PROJECT_DIR%sdkconfig.board.xiao-esp32s3-sense
call idf.py -B build_xiao set-target esp32s3
call idf.py -B build_xiao -D SDKCONFIG_DEFAULTS="%SDKCONFIG_DEFAULTS%" build
if errorlevel 1 (
    echo ERROR: Build failed for XIAO ESP32-S3 Sense Board
) else (
    copy build_xiao\xiaozhi-esp32.bin "%BUILD_OUTPUT%\xiaozhi-xiao-esp32s3-sense.bin"
    echo SUCCESS: XIAO ESP32-S3 Sense Board firmware built
)

echo.
echo ========================================
echo Build Complete!
echo Firmware files are in: %BUILD_OUTPUT%
echo ========================================
dir "%BUILD_OUTPUT%\*.bin"

endlocal
