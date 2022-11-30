#ifndef DANCE_MATRIX_ANIMATION_H
#define DANCE_MATRIX_ANIMATION_H

#include <cstdint>
#include <optional>
#include <vector>
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
    AnimationStatus tick(uint32_t time);
    void draw(uint16_t x, uint16_t y);
    void printInfos() const;
    ~Animation() = default;

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

class AnimationPack {
public:
    static std::optional<AnimationPack> FromDir(FsFile dir);
    AnimationPack() = default;
    void addAnimation(Animation &animation);
    void update(uint32_t time);
    void printInfos() const;
    [[nodiscard]] const char *getName() const;
    ~AnimationPack() = default;

private:
    char name[32]{};
    std::vector<Animation> animations;
};

#endif /* ! DANCE_MATRIX_ANIMATION_H */
