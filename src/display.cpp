#include "display.h"

static volatile DMAMEM MatrixRefreshType::rowDataStruct rowsDataBuffer[kDmaBufferRows];
MatrixRefreshType matrixRefresh(kDmaBufferRows, rowsDataBuffer);
MatrixType matrix(kDmaBufferRows, rowsDataBuffer);

static rgb24 backgroundLayerBitmap[2 * kMatrixWidth * kMatrixHeight];
static uint16_t backgroundLayerColorCorrectionLUT[256];
static BackgroundLayerType backgroundLayer(backgroundLayerBitmap, kMatrixWidth, kMatrixHeight,
                                           backgroundLayerColorCorrectionLUT);

MatrixRefreshType &getMatrixRefresh() {
    return matrixRefresh;
}

MatrixType &getMatrix() {
    return matrix;
}

BackgroundLayerType &getBackgroundLayer() {
    return backgroundLayer;
}
