#include "context.h"

void Context::initialize() {
    // Initialize the SD.
    if (!sd.begin(SD_CONFIG)) {
        Serial.println(F("SD not present"));
        sdPresent = false;
        return;
    }

    sdPresent = true;
    Serial.println(F("Initialized SD"));
}

void Context::update(uint32_t time) {
    if (animation_packs.empty())
        return;
    getCurrentAnimationPack().update(time);
}

SdFs &Context::getSd() {
    return sd;
}

bool Context::isSdPresent() const {
    return sdPresent;
}

void Context::addAnimationPack(AnimationPack &animation_pack) {
    animation_packs.push_back(animation_pack);
}

AnimationPack &Context::getCurrentAnimationPack() {
    return animation_packs[current_animation_pack];
}

std::vector<AnimationPack> const &Context::getAnimationPacks() {
    return animation_packs;
}

void Context::setCurrentAnimationPack(uint8_t pack) {
    current_animation_pack = pack;
}
