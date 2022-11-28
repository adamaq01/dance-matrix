#include "bitmap.h"

#include "display.h"

void bitmap_animation_draw(uint16_t x, uint16_t y, const bitmap_animation *animation) {
    for (uint8_t frame = 0; frame < animation->frames; frame++) {
        for (uint8_t i = 0; i < animation->height; i++) {
            for (uint8_t j = 0; j < animation->width; j++) {
                SM_RGB pixel = { animation->pixel_data[frame][(i * animation->width + j) * 3 + 0],
                                 animation->pixel_data[frame][(i * animation->width + j) * 3 + 1],
                                 animation->pixel_data[frame][(i * animation->width + j) * 3 + 2] };

                getBackgroundLayer().drawPixel(x + j, y + i, pixel);
            }
        }
        getBackgroundLayer().swapBuffers();
        delay(animation->delay);
    }
}
