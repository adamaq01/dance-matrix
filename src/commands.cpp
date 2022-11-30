#include "commands.h"

#include <sstream>
#include <string>
#include <Arduino.h>
#include "context.h"
#include "display.h"

#define COMMAND_STARTER F("C_START")
#define COMMAND_TERMINATOR F("C_END")
#define COMMAND_TERMINATOR_ERROR F("C_ERR")
#define PARSE(var, message)                                                                        \
    ss >> var;                                                                                     \
    if (ss.fail()) {                                                                               \
        Serial.println(F(message));                                                                \
        Serial.println(COMMAND_TERMINATOR_ERROR);                                                  \
        return;                                                                                    \
    }

void handleCommand(Context &context, Command command, const char *args, size_t len) {
    std::stringstream ss(std::string(args, len));
    Serial.println(COMMAND_STARTER);
    switch (command) {
        case HELP:
            Serial.println(F("h - lists all commands"));
            Serial.println(F("p - list available animation packs"));
            Serial.println(F("s <pack> - select animation pack"));
            Serial.println(F("i - list infos about current animation pack"));
            Serial.println(F("b <brightness> - set brightness (0-255)"));
            Serial.println(COMMAND_TERMINATOR);
            break;
        case PACKS:
            for (auto &pack : context.getAnimationPacks()) {
                Serial.println(pack.getName());
            }
            Serial.println(COMMAND_TERMINATOR);
            break;
        case SELECT:
            size_t pack;
            PARSE(pack, "Failed to parse pack")
            if (pack >= context.getAnimationPacks().size()) {
                Serial.println(F("Pack does not exist"));
                Serial.println(COMMAND_TERMINATOR_ERROR);
                return;
            }
            context.setCurrentAnimationPack(pack);
            Serial.println(COMMAND_TERMINATOR);
            break;
        case INFOS:
            if (context.getAnimationPacks().empty()) {
                Serial.println(F("No animation packs loaded"));
                Serial.println(COMMAND_TERMINATOR_ERROR);
                return;
            }
            context.getCurrentAnimationPack().printInfos();
            Serial.println(COMMAND_TERMINATOR);
            break;
        case BRIGHTNESS:
            uint16_t brightness; // stringstream would not parse uint8_t as a number
            PARSE(brightness, "Failed to parse brightness")
            if (brightness > 255 || brightness < 0) {
                Serial.println(F("Brightness must be between 0 and 255"));
                Serial.println(COMMAND_TERMINATOR_ERROR);
                return;
            }
            getBackgroundLayer().setBrightness(brightness);
            Serial.println(COMMAND_TERMINATOR);
            break;
        default:
            Serial.println(F("Unknown command"));
            Serial.println(COMMAND_TERMINATOR_ERROR);
            break;
    }
}
