#ifndef DANCE_MATRIX_BITMAP_H
#define DANCE_MATRIX_BITMAP_H

#include <cstdint>

typedef struct {
    uint8_t width;
    uint8_t height;
    uint8_t bytes_per_pixel; /* 2:RGB16, 3:RGB, 4:RGBA */
    uint8_t pixel_data[32 * 32 * 3 + 1];
} bitmap;

typedef struct {
    uint8_t width;
    uint8_t height;
    uint8_t bytes_per_pixel; /* 2:RGB16, 3:RGB, 4:RGBA */
    uint8_t frames;
    uint16_t delay;
    uint8_t pixel_data[32][32 * 32 * 3];
} bitmap_animation;

void bitmap_animation_draw(uint16_t x, uint16_t y, const bitmap_animation *animation);

#endif /* ! DANCE_MATRIX_BITMAP_H */
