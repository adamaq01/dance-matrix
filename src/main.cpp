#include <Arduino.h>

#include "animation.h"
#include "context.h"
#include "display.h"
#include "sd.h"

static Context context;

void initSerial() {
    Serial.begin(9600);

    // Wait for USB Serial
    while (!Serial) {
        yield();
    }

    Serial.println(F("Serial ready"));
}

void setup() {
    initSerial();
    context.initialize();

    if (context.isSdPresent()) {
        FsFile animationsDir = context.getSd().open("animations/");
        while (true) {
            FsFile entry = animationsDir.openNextFile();
            if (!entry)
                break;
            if (entry.isDirectory())
                if (auto pack = AnimationPack::FromDir(entry))
                    context.addAnimationPack(*pack);
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
    context.update(time);
}
