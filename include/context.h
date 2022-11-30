#ifndef DANCE_MATRIX_CONTEXT_H
#define DANCE_MATRIX_CONTEXT_H

#include <cstdint>
#include <iterator>
#include <vector>
#include "animation.h"
#include "sd.h"

class Context {
public:
    Context() = default;
    ~Context() = default;

    void initialize();
    void update(uint32_t time);

    SdFs &getSd();
    [[nodiscard]] bool isSdPresent() const;

    void addAnimationPack(AnimationPack &animation_pack);
    AnimationPack &getCurrentAnimationPack();
    void setCurrentAnimationPack(uint8_t pack);
    std::vector<AnimationPack> const &getAnimationPacks();

private:
    SdFs sd{};
    bool sdPresent{};
    uint8_t current_animation_pack{};
    std::vector<AnimationPack> animation_packs;
};

#endif /* ! DANCE_MATRIX_CONTEXT_H */
