#ifndef PX_CORE_CONSOLE_ESCAPE_C
#define PX_CORE_CONSOLE_ESCAPE_C

#include "escape.h"

PxEscapeType
pxEscapeSetType(PxEscape* self, PxEscapeType value)
{
    pxu8 result = self->type;

    self->type = value;

    return result;
}

pxb8
pxEscapeInsertTail(PxEscape* self, pxuword value)
{
    pxiword index = self->size;

    if (index < 0 || index >= PX_ESCAPE_ITEMS)
        return 0;

    self->size += 1;

    self->items[index] = value;

    return 1;
}

pxb8
pxEscapeRead(PxEscape* self, pxiword index, pxuword* value)
{
    if (index < 0 || index >= self->size)
        return 0;

    if (value != 0) *value = self->items[index];

    return 1;
}

pxuword
pxEscapeReadOr(PxEscape* self, pxiword index, pxuword value)
{
    if (index < 0 || index >= self->size)
        return value;

    return self->items[index];
}

pxb8
pxEscapeFromString8(PxEscape* self, PxString8 string, pxiword* size)
{
    if (string.length <= 2) {
        if (size != 0)
            *size = string.length;

        return 0;
    }

    if (string.memory[0] != 0x1b) {
        if (size != 0) *size = 1;

        return 0;
    }

    if (string.memory[1] != 0x5b) {
        if (size != 0) *size = 2;;

        return 0;
    }

    PxString8 left  = {0};
    PxString8 right = {0};
    pxiword   index = 2;

    right = pxString8Slice(string, index, string.length - 1);

    while (right.length > 0) {
        index += pxString8Split(right, pxs8(";"), &left, &right);

        if (pxEscapeItemFromString8(self, left) == 0)
            break;
    }

    switch (string.memory[index]) {
        case PX_ASCII_LOWER_U:
            pxEscapeSetType(self, PX_ESCAPE_KEYBOARD);
        break;

        case PX_ASCII_LOWER_M:
            pxEscapeSetType(self, PX_ESCAPE_GRAPHICS);
        break;

        case PX_ASCII_UPPER_A:
        case PX_ASCII_UPPER_B:
        case PX_ASCII_UPPER_C:
        case PX_ASCII_UPPER_D:
            pxEscapeSetType(self, PX_ESCAPE_MOVEMENT);
        break;

        default: break;
    }

    if (size != 0) *size = index + 1;

    if (self->type == PX_ESCAPE_NONE) return 0;

    return 1;
}

pxb8
pxEscapeItemFromString8(PxEscape* self, PxString8 string)
{
    PxFormatOption options = PX_FORMAT_OPTION_NONE;
    pxuword        value   = 0;

    switch (pxString8Contains(string, pxs8(":"))) {
        case 0: {
            pxb8 state = pxUnsignedFromString8(
                &value, 10, options, string);

            if (state != 0)
                pxEscapeInsertTail(self, value);

            return state;
        } break;

        default: break;
    }

    return 0;
}

#endif // PX_CORE_CONSOLE_ESCAPE_C
