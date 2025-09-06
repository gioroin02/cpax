#ifndef PX_CORE_CONSOLE_SEQUENCE_C
#define PX_CORE_CONSOLE_SEQUENCE_C

#include "sequence.h"

pxb8
pxConsoleSequenceFromString8(PxConsoleSequence* self, PxString8 string)
{
    if (string.length <= 0) return 0;

    switch (string.memory[0]) {
        case PX_ASCII_BELL:
        case PX_ASCII_BACK_SPACE:
        case PX_ASCII_HORIZONTAL_TAB:
        case PX_ASCII_LINE_FEED:
        case PX_ASCII_VERTICAL_TAB:
        case PX_ASCII_PAGE_FEED:
        case PX_ASCII_CARRIAGE_RETURN: {
            if (string.length > 1)
                return 0;

            self->func = string.memory[0];

            return 1;
        } break;

        case PX_ASCII_ESCAPE: {
            if (string.length > 1)
                break;

            self->func = string.memory[0];

            return 1;
        } break;

        default: return 0;
    }

    switch (string.memory[1]) {
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
        case PX_ASCII_LOWER_Z: {
            self->size = 2;

            self->args[0] = string.memory[1];
            self->args[1] = 3;

            return 1;
        } break;

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
        case PX_ASCII_UPPER_Z: {
            self->size = 2;

            self->args[0] = string.memory[1];
            self->args[1] = 4;

            return 1;
        } break;

        default: break;
    }

    return 0;
}

PxConsoleEvent
pxConsoleEventFromSequence(PxConsoleSequence* sequence)
{
    PxConsoleEvent result = {.type = PX_CONSOLE_EVENT_NONE};

    switch (sequence->func) {
        case PX_ASCII_NULL: {
            pxuword modifs  = sequence->args[1];
            pxi32   unicode = sequence->args[0];

            result = pxConsoleEventKeybdPress(
                PX_CONSOLE_KEYBD_A + unicode, modifs, unicode);
        } break;

        case PX_ASCII_ESCAPE: {
            result = pxConsoleEventKeybdPress(
                PX_CONSOLE_KEYBD_ESCAPE, 0, PX_ASCII_ESCAPE);
        } break;

        case PX_ASCII_UPPER_A: {
            result = pxConsoleEventKeybdPress(
                PX_CONSOLE_KEYBD_ARROW_UP, 0, 0);
        } break;

        case PX_ASCII_UPPER_B: {
            result = pxConsoleEventKeybdPress(
                PX_CONSOLE_KEYBD_ARROW_DOWN, 0, 0);
        } break;

        case PX_ASCII_UPPER_C: {
            result = pxConsoleEventKeybdPress(
                PX_CONSOLE_KEYBD_ARROW_RIGHT, 0, 0);
        } break;

        case PX_ASCII_UPPER_D: {
            result = pxConsoleEventKeybdPress(
                PX_CONSOLE_KEYBD_ARROW_LEFT, 0, 0);
        } break;

        case PX_ASCII_UPPER_H: {
            result = pxConsoleEventKeybdPress(
                PX_CONSOLE_KEYBD_HOME, 0, 0);
        } break;

        case PX_ASCII_UPPER_F: {
            result = pxConsoleEventKeybdPress(
                PX_CONSOLE_KEYBD_END, 0, 0);
        } break;

        case PX_ASCII_TILDE: {
            if (sequence->size <= 0) return result;

            pxiword button = PX_CONSOLE_KEYBD_HOME;

            switch (sequence->args[0]) {
                case 5: button = PX_CONSOLE_KEYBD_PAGE_UP;   break;
                case 6: button = PX_CONSOLE_KEYBD_PAGE_DOWN; break;

                case 11: button = PX_CONSOLE_KEYBD_FUNC1; break;
                case 12: button = PX_CONSOLE_KEYBD_FUNC2; break;
                case 13: button = PX_CONSOLE_KEYBD_FUNC3; break;
                case 14: button = PX_CONSOLE_KEYBD_FUNC4; break;
                case 15: button = PX_CONSOLE_KEYBD_FUNC5; break;

                case 17: button = PX_CONSOLE_KEYBD_FUNC6;  break;
                case 18: button = PX_CONSOLE_KEYBD_FUNC7;  break;
                case 19: button = PX_CONSOLE_KEYBD_FUNC8;  break;
                case 20: button = PX_CONSOLE_KEYBD_FUNC9;  break;
                case 21: button = PX_CONSOLE_KEYBD_FUNC10; break;

                case 23: button = PX_CONSOLE_KEYBD_FUNC11; break;
                case 24: button = PX_CONSOLE_KEYBD_FUNC12; break;

                default: break;
            }

            if (button != PX_CONSOLE_KEYBD_NONE)
                result = pxConsoleEventKeybdPress(button, 0, 0);
        } break;

        default: break;
    }

    return result;
}

#endif // PX_CORE_CONSOLE_SEQUENCE_C
