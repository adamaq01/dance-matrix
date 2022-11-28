#include "animation.h"

#include <iostream>
#include <sstream>
#include <string>
#include "display.h"

bool Animation::tick(uint32_t time) {
    if (frame_count <= 1)
        return FINISHED;

    if (time - last_frame_time > frame_delay) {
        frame++;
        if (frame >= frame_count) {
            frame = 0;
        }
        last_frame_time = time;

        return frame == 0 ? FINISHED : RUNNING;
    }

    return WAITING;
}

void Animation::draw(uint16_t x, uint16_t y) {
    uint64_t buf_len = width * height * bytes_per_pixel;
    uint8_t buffer[buf_len];
    file.seekSet(frame * buf_len);
    file.read(buffer, buf_len);

    for (uint16_t i = 0; i < height; i++) {
        for (uint16_t j = 0; j < width; j++) {
            uint64_t index = (i * width + j) * bytes_per_pixel;
            switch (bytes_per_pixel) {
                case RGB16:
                    getBackgroundLayer().drawPixel(
                        x + j, y + i, SM_RGB(*reinterpret_cast<const uint16_t *>(buffer + index)));
                    break;
                case RGB:
                case RGBA:
                    getBackgroundLayer().drawPixel(
                        x + j, y + i, *reinterpret_cast<const SM_RGB *>(buffer + index));
                    break;
                default:
                    break;
            }
        }
    }

    getBackgroundLayer().swapBuffers();
}

#define PARSE(var)                                                                                 \
    ss >> var;                                                                                     \
    if (ss.fail()) {                                                                               \
        Serial.println(F("Failed to parse animation"));                                            \
        return {};                                                                                 \
    }

std::optional<Animation> Animation::FromFile(FsFile file) {
    Animation animation;
    animation.file = std::move(file);

    char buf[32] = { 0 };
    size_t len = animation.file.getName(buf, 32);
    if (!(buf[len - 1] == 'i' && buf[len - 2] == 'n' && buf[len - 3] == 'a'
          && buf[len - 4] == '.')) {
        Serial.println(F("Not an animation"));
        return {};
    }
    char single;
    std::stringstream ss(buf);
    uint16_t temp;
    PARSE(temp);
    animation.button = static_cast<uint8_t>(temp);
    ss >> single;
    PARSE(animation.width);
    ss >> single;
    PARSE(animation.height);
    ss >> single;
    PARSE(temp);
    animation.bytes_per_pixel = static_cast<BytesPerPixel>(temp);
    ss >> single;
    PARSE(animation.frame_count);
    ss >> single;
    PARSE(animation.frame_delay);

    return animation;
}

void Animation::printInfos() {
    char buf[32] = { 0 };
    file.getName(buf, 32);
    Serial.print(F("Animation: "));
    Serial.println(buf);
    Serial.print(F("- Button: "));
    Serial.println(button);
    Serial.print(F("- Width: "));
    Serial.println(width);
    Serial.print(F("- Height: "));
    Serial.println(height);
    Serial.print(F("- Bytes per pixel: "));
    Serial.println(bytes_per_pixel);
    Serial.print(F("- Frame count: "));
    Serial.println(frame_count);
    Serial.print(F("- Frame delay: "));
    Serial.println(frame_delay);
}
