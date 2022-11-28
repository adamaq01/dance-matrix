#include <vector>
#include <Arduino.h>
#include "animation.h"
#include "display.h"
#include "sd.h"

void initSerial() {
    Serial.begin(9600);

    // Wait for USB Serial
    while (!Serial) {
        yield();
    }

    Serial.println(F("Serial ready"));
}

SdFs sd;
bool sdPresent = false;

void initSd() {
    // Initialize the SD.
    if (!sd.begin(SD_CONFIG)) {
        Serial.println(F("SD not present"));
        sdPresent = false;
        return;
    }

    sdPresent = true;
    Serial.println(F("Initialized SD"));
}

std::vector<Animation> animations;

void findAnimations(FsFile dir) {
    while (true) {
        FsFile entry = dir.openNextFile();
        if (!entry)
            break;
        if (entry.isDirectory())
            continue;
        if (auto animation = Animation::FromFile(entry)) {
            animation->printInfos();
            animations.push_back(std::move(*animation));
        } else {
            entry.close();
        }
    }
}

void setup() {
    initSerial();
    initSd();

    if (sdPresent) {
        FsFile animationsDir = sd.open("animations/");
        while (true) {
            FsFile entry = animationsDir.openNextFile();
            if (!entry)
                break;
            if (entry.isDirectory())
                findAnimations(entry);
            entry.close();
        }
        animationsDir.close();
    }

    getMatrix().addLayer(&getBackgroundLayer());
    getMatrix().begin();

    getMatrix().setBrightness(128);

    getBackgroundLayer().fillScreen({ 0, 0, 0 });
}

void loop() {
    uint32_t time = millis();
    for (auto &item : animations) {
        if (item.tick(time)) {
            item.draw(0, 0);
        }
    }
}
