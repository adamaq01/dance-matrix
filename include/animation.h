#ifndef DANCE_MATRIX_ANIMATION_H
#define DANCE_MATRIX_ANIMATION_H

#include <cstdint>
#include <optional>
#include "sd.h"

enum BytesPerPixel {
    UNKNOWN,
    RGB16 = 2,
    RGB = 3,
    RGBA = 4,
};

enum AnimationStatus {
    WAITING,
    RUNNING,
    FINISHED,
};

class Animation {
public:
    static std::optional<Animation> FromFile(FsFile file);
    bool tick(uint32_t time);
    void draw(uint16_t x, uint16_t y);
    void printInfos();

private:
    FsFile file;
    uint8_t button{};
    uint16_t width{};
    uint16_t height{};
    BytesPerPixel bytes_per_pixel{};
    uint16_t frame_count{};
    uint16_t frame_delay{};
    uint16_t frame{};
    uint32_t last_frame_time{};
};

#endif /* ! DANCE_MATRIX_ANIMATION_H */
