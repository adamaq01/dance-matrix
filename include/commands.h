#ifndef DANCE_MATRIX_COMMANDS_H
#define DANCE_MATRIX_COMMANDS_H

#include <cstdint>
#include "context.h"

enum Command {
    HELP = 'h',
    PACKS = 'p',
    SELECT = 's',
    INFOS = 'i',
    BRIGHTNESS = 'b',
};

void handleCommand(Context &context, Command command, const char *args, size_t len);

#endif /* ! DANCE_MATRIX_COMMANDS_H */
