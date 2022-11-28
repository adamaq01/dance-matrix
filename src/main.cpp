#include <Arduino.h>
#include "bitmap.h"
#include "display.h"
#include "sd.h"

void serial_init() {
    Serial.begin(9600);

    // Wait for USB Serial
    while (!Serial) {
        yield();
    }

    Serial.println(F("Serial ready"));
}

void setup() {
    serial_init();

    getMatrix().addLayer(&getBackgroundLayer());
    getMatrix().begin();

    getMatrix().setBrightness(128);

    getBackgroundLayer().fillScreen({ 0, 0, 0 });
}

#include "pump_anim.cpp"

void loop() {
    uint16_t x = (kMatrixWidth / 2) - (pumparrow_anim.width / 2);
    uint16_t y = (kMatrixHeight / 2) - (pumparrow_anim.height / 2);
    bitmap_animation_draw(x, y, &pumparrow_anim);
}
