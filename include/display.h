#ifndef DANCE_MATRIX_DISPLAY_H
#define DANCE_MATRIX_DISPLAY_H

#include <cstdint>

#include <MatrixHardware_Teensy4_ShieldV5.h> // SmartLED Shield for Teensy 4 (V5)
#include <SmartMatrix.h>

#define COLOR_DEPTH 24
const uint16_t kMatrixWidth = 32;
const uint16_t kMatrixHeight = 32;
// Tradeoff of color quality vs refresh rate, max brightness, and RAM usage. On Teensy, multiples of
// 3, up to 48: 3, 6, 9, 12, 15, 18, 21, 24, 27, 30, 33, 36, 39, 42, 45, 48.
const uint8_t kRefreshDepth = 36;
// known working: 2-4, use 2 to save RAM, more to keep from dropping frames and automatically
// lowering refresh rate.
const uint8_t kDmaBufferRows = 4;
// Choose the configuration that matches your panels
// (https://github.com/pixelmatix/SmartMatrix/wiki)
const uint8_t kPanelType = SM_PANELTYPE_HUB75_32ROW_MOD16SCAN;
const uint32_t kMatrixOptions = (SM_HUB75_OPTIONS_NONE);
const uint8_t kBackgroundLayerOptions = (SM_BACKGROUND_OPTIONS_NONE);

typedef rgb24 SM_RGB;
typedef SmartMatrixRefreshT4<kRefreshDepth, kMatrixWidth, kMatrixHeight, kPanelType, kMatrixOptions>
    MatrixRefreshType;
typedef SmartMatrixHub75Calc<kRefreshDepth, kMatrixWidth, kMatrixHeight, kPanelType, kMatrixOptions>
    MatrixType;
typedef SMLayerBackground<rgb24, kBackgroundLayerOptions> BackgroundLayerType;

MatrixRefreshType &getMatrixRefresh();
MatrixType &getMatrix();
BackgroundLayerType &getBackgroundLayer();

#endif /* ! DANCE_MATRIX_DISPLAY_H */
