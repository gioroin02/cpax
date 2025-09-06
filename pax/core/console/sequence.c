#ifndef PX_CORE_CONSOLE_SEQUENCE_C
#define PX_CORE_CONSOLE_SEQUENCE_C

#include "sequence.h"

pxb8
pxConsoleSequenceFromString8(PxConsoleSequence* self, PxString8 string)
{
    pxu8*   memory = string.memory;
    pxiword length = string.length;

    if (length <= 0 || memory[0] != PX_ASCII_ESCAPE)
        return 0;

    if (length == 1) return 1;

    switch (memory[1]) {
        case PX_ASCII_SQUARE_LEFT: {
            PxString8 left  = {0};
            PxString8 right = pxString8Slice(string, 2, string.length - 1);

            pxu8 value = 0;

            while (right.length > 0) {
                pxString8Split(right, pxs8(";"), &left, &right);

                pxb8 state = pxUnsigned8FromString8(&value,
                    10, PX_FORMAT_OPTION_NONE, left);

                if (state != 0 && self->size < PX_CONSOLE_SEQUENCE_ARGS) {
                    self->args[self->size] = value;

                    self->size += 1;
                }
            }

            self->func = string.memory[string.length - 1];

            return 1;
        } break;

        default: break;
    }

    return 0;
}

#endif // PX_CORE_CONSOLE_SEQUENCE_C
