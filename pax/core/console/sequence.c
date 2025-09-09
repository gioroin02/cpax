#ifndef PX_CORE_CONSOLE_SEQUENCE_C
#define PX_CORE_CONSOLE_SEQUENCE_C

#include "sequence.h"

pxu8
pxConsoleSequenceSetFunction(PxConsoleSequence* self, pxu8 value)
{
    pxu8 result = self->func;

    self->func = value;

    return result;
}

pxu8
pxConsoleSequenceAddArgument(PxConsoleSequence* self, pxu8 value)
{
    pxiword index = self->size;

    if (index < 0 || index >= PX_CONSOLE_SEQUENCE_ARGS)
        return 0;

    self->size += 1;

    self->args[index] = value;

    return 1;
}

pxiword
pxConsoleSequenceFromString8(PxConsoleSequence* self, PxString8 string)
{
    pxiword index = 0;

    if (string.length <= 0) return string.length;

    switch (string.memory[index]) {
        case PX_ASCII_BELL:
        case PX_ASCII_BACK_SPACE:
        case PX_ASCII_HORIZONTAL_TAB:
        case PX_ASCII_LINE_FEED:
        case PX_ASCII_VERTICAL_TAB:
        case PX_ASCII_PAGE_FEED:
        case PX_ASCII_CARRIAGE_RETURN: {
            if (string.length <= 1)
                self->func = string.memory[index];

            return index + 1;
        } break;

        case PX_ASCII_DELETE: {
            if (string.length <= 1)
                self->func = PX_ASCII_BACK_SPACE;

            return index + 1;
        } break;

        case PX_ASCII_ESCAPE: {
            if (string.length > 1)
                break;

            self->func = string.memory[index];

            return index + 1;
        } break;

        default: return index;
    }

    index += 1;

    PxString8 left  = {0};
    PxString8 right = {0};
    pxu8      value = 0;

    switch (string.memory[index]) {
        case PX_ASCII_SQUARE_LEFT: {
            if (string.length <= 2) return string.length;

            right = pxString8Slice(string,
                index + 1, string.length - 1);

            for (; right.length > 0; index += left.length + 1) {
                pxString8Split(right, pxs8(";"), &left, &right);

                pxb8 state = pxUnsigned8FromString8(&value,
                    10, PX_FORMAT_OPTION_NONE, left);

                if (state != 0)
                    pxConsoleSequenceAddArgument(self, value);
                else
                    return index + 1;
            }

            pxConsoleSequenceSetFunction(self,
                string.memory[string.length - 1]);

            return string.length;
        } break;

        case PX_ASCII_LOWER_A:
        case PX_ASCII_LOWER_B:
        case PX_ASCII_LOWER_C:
        case PX_ASCII_LOWER_D:
        case PX_ASCII_LOWER_E:
        case PX_ASCII_LOWER_F:
        case PX_ASCII_LOWER_G:
        case PX_ASCII_LOWER_H:
        case PX_ASCII_LOWER_I:
        case PX_ASCII_LOWER_J:
        case PX_ASCII_LOWER_K:
        case PX_ASCII_LOWER_L:
        case PX_ASCII_LOWER_M:
        case PX_ASCII_LOWER_N:
        case PX_ASCII_LOWER_O:
        case PX_ASCII_LOWER_P:
        case PX_ASCII_LOWER_Q:
        case PX_ASCII_LOWER_R:
        case PX_ASCII_LOWER_S:
        case PX_ASCII_LOWER_T:
        case PX_ASCII_LOWER_U:
        case PX_ASCII_LOWER_V:
        case PX_ASCII_LOWER_W:
        case PX_ASCII_LOWER_X:
        case PX_ASCII_LOWER_Y:
        case PX_ASCII_LOWER_Z:
            self->size = 2;

            self->args[0] = string.memory[index];
            self->args[1] = 3;
        return index + 1;

        case PX_ASCII_UPPER_A:
        case PX_ASCII_UPPER_B:
        case PX_ASCII_UPPER_C:
        case PX_ASCII_UPPER_D:
        case PX_ASCII_UPPER_E:
        case PX_ASCII_UPPER_F:
        case PX_ASCII_UPPER_G:
        case PX_ASCII_UPPER_H:
        case PX_ASCII_UPPER_I:
        case PX_ASCII_UPPER_J:
        case PX_ASCII_UPPER_K:
        case PX_ASCII_UPPER_L:
        case PX_ASCII_UPPER_M:
        case PX_ASCII_UPPER_N:
        case PX_ASCII_UPPER_O:
        case PX_ASCII_UPPER_P:
        case PX_ASCII_UPPER_Q:
        case PX_ASCII_UPPER_R:
        case PX_ASCII_UPPER_S:
        case PX_ASCII_UPPER_T:
        case PX_ASCII_UPPER_U:
        case PX_ASCII_UPPER_V:
        case PX_ASCII_UPPER_W:
        case PX_ASCII_UPPER_X:
        case PX_ASCII_UPPER_Y:
        case PX_ASCII_UPPER_Z:
            self->size = 2;

            self->args[0] = string.memory[index];
            self->args[1] = 4;

        return index + 1;

        default: break;
    }

    return 0;
}

#endif // PX_CORE_CONSOLE_SEQUENCE_C
