// image_to_jpeg.h - Efficient JPEG encoding interface for image conversion
// JPEG encoding implementation saving about 8KB SRAM
#pragma once
#include "sdkconfig.h"
#ifndef CONFIG_IDF_TARGET_ESP32

#include <linux/videodev2.h>
#include <stddef.h>
#include <stdint.h>


typedef uint32_t v4l2_pix_fmt_t; // see linux/videodev2.h for details

#ifdef __cplusplus
extern "C" {
#endif

// JPEG output callback function type
// arg: user defined argument, index: current data index, data: JPEG data block,
// len: data block length Return: actual processed bytes
typedef size_t (*jpg_out_cb)(void *arg, size_t index, const void *data,
                             size_t len);

/**
 * @brief Efficiently convert image format to JPEG
 *
 * This function uses an optimized JPEG encoder, key features:
 * - Saves about 8KB of SRAM usage (static variables changed to heap allocation)
 * - Supports multiple image format inputs
 * - High quality JPEG output
 *
 * @param src       Source image data
 * @param src_len   Source image data length
 * @param width     Image width
 * @param height    Image height
 * @param format    Image format (PIXFORMAT_RGB565, PIXFORMAT_RGB888, etc.)
 * @param quality   JPEG quality (1-100)
 * @param out       Output JPEG data pointer (caller needs to free)
 * @param out_len   Output JPEG data length
 *
 * @return true success, false failure
 */
bool image_to_jpeg(uint8_t *src, size_t src_len, uint16_t width,
                   uint16_t height, v4l2_pix_fmt_t format, uint8_t quality,
                   uint8_t **out, size_t *out_len);

/**
 * @brief Convert image format to JPEG (callback version)
 *
 * Use callback function to process JPEG output data, suitable for streaming or
 * chunked processing:
 * - Saves about 8KB of SRAM usage (static variables changed to heap allocation)
 * - Supports streaming output, no need to pre-allocate large buffer
 * - Process JPEG data chunk by chunk via callback function
 *
 * @param src       Source image data
 * @param src_len   Source image data length
 * @param width     Image width
 * @param height    Image height
 * @param format    Image format
 * @param quality   JPEG quality (1-100)
 * @param cb        Output callback function
 * @param arg       User argument passed to callback function
 *
 * @return true success, false failure
 */
bool image_to_jpeg_cb(uint8_t *src, size_t src_len, uint16_t width,
                      uint16_t height, v4l2_pix_fmt_t format, uint8_t quality,
                      jpg_out_cb cb, void *arg);

#ifdef __cplusplus
}
#endif

#endif // ndef CONFIG_IDF_TARGET_ESP32
