#ifndef PX_FORMAT_STRING8_C
#define PX_FORMAT_STRING8_C

#include "string8.h"

pxbool8
pxWord8FromString8(pxword8* self, PxFormatOptions options, PxString8 string)
{
    PxFormatFlag flags = options.flags;
    pxword8      radix = options.radix;
    pxint        index = 0;
    pxword8      temp  = 0;

    if (string.length <= 0) return 0;

    switch (string.memory[index]) {
        case PX_ASCII_PLUS:
            if ((flags & PX_FORMAT_FLAG_LEADING_PLUS) == 0)
                return 0;

            index += 1;
        break;

        default: break;
    }

    if ((flags & PX_FORMAT_FLAG_LEADING_ZERO) == 0) {
        pxint32 unicode = string.memory[index];

        if (string.length > index + 1 && unicode == PX_ASCII_ZERO)
            return 0;
    }

    for (; index < string.length; index += 1) {
        pxword8 digit = pxAsciiDigitValue(string.memory[index], radix);

        if (digit < 0 || digit >= radix) return 0;

        if (temp > (PX_WORD8_MAX - digit) / radix)
            return 0;

        temp = temp * radix + digit;
    }

    if (self != 0) *self = temp;

    return 1;
}

pxbool8
pxWord16FromString8(pxword16* self, PxFormatOptions options, PxString8 string)
{
    PxFormatFlag flags = options.flags;
    pxword8      radix = options.radix;
    pxint        index = 0;
    pxword16     temp  = 0;

    if (string.length <= 0) return 0;

    switch (string.memory[index]) {
        case PX_ASCII_PLUS:
            if ((flags & PX_FORMAT_FLAG_LEADING_PLUS) == 0)
                return 0;

            index += 1;
        break;

        default: break;
    }

    if ((flags & PX_FORMAT_FLAG_LEADING_ZERO) == 0) {
        pxint32 unicode = string.memory[index];

        if (string.length > index + 1 && unicode == PX_ASCII_ZERO)
            return 0;
    }

    for (; index < string.length; index += 1) {
        pxword8 digit = pxAsciiDigitValue(string.memory[index], radix);

        if (digit < 0 || digit >= radix) return 0;

        if (temp > (PX_WORD16_MAX - digit) / radix)
            return 0;

        temp = temp * radix + digit;
    }

    if (self != 0) *self = temp;

    return 1;
}

pxbool8
pxWord32FromString8(pxword32* self, PxFormatOptions options, PxString8 string)
{
    PxFormatFlag flags = options.flags;
    pxword8      radix = options.radix;
    pxint        index = 0;
    pxword32     temp  = 0;

    if (string.length <= 0) return 0;

    switch (string.memory[index]) {
        case PX_ASCII_PLUS:
            if ((flags & PX_FORMAT_FLAG_LEADING_PLUS) == 0)
                return 0;

            index += 1;
        break;

        default: break;
    }

    if ((flags & PX_FORMAT_FLAG_LEADING_ZERO) == 0) {
        pxint32 unicode = string.memory[index];

        if (string.length > index + 1 && unicode == PX_ASCII_ZERO)
            return 0;
    }

    for (; index < string.length; index += 1) {
        pxword8 digit = pxAsciiDigitValue(string.memory[index], radix);

        if (digit < 0 || digit >= radix) return 0;

        if (temp > (PX_WORD32_MAX - digit) / radix)
            return 0;

        temp = temp * radix + digit;
    }

    if (self != 0) *self = temp;

    return 1;
}

pxbool8
pxWord64FromString8(pxword64* self, PxFormatOptions options, PxString8 string)
{
    PxFormatFlag flags = options.flags;
    pxword8      radix = options.radix;
    pxint        index = 0;
    pxword64     temp  = 0;

    if (string.length <= 0) return 0;

    switch (string.memory[index]) {
        case PX_ASCII_PLUS:
            if ((flags & PX_FORMAT_FLAG_LEADING_PLUS) == 0)
                return 0;

            index += 1;
        break;

        default: break;
    }

    if ((flags & PX_FORMAT_FLAG_LEADING_ZERO) == 0) {
        pxint32 unicode = string.memory[index];

        if (string.length > index + 1 && unicode == PX_ASCII_ZERO)
            return 0;
    }

    for (; index < string.length; index += 1) {
        pxword8 digit = pxAsciiDigitValue(string.memory[index], radix);

        if (digit < 0 || digit >= radix) return 0;

        if (temp > (PX_WORD64_MAX - digit) / radix)
            return 0;

        temp = temp * radix + digit;
    }

    if (self != 0) *self = temp;

    return 1;
}

pxbool8
pxWordFromString8(pxword* self, PxFormatOptions options, PxString8 string)
{
    PxFormatFlag flags = options.flags;
    pxword8      radix = options.radix;
    pxint        index = 0;
    pxword       temp  = 0;

    if (string.length <= 0) return 0;

    switch (string.memory[index]) {
        case PX_ASCII_PLUS:
            if ((flags & PX_FORMAT_FLAG_LEADING_PLUS) == 0)
                return 0;

            index += 1;
        break;

        default: break;
    }

    if ((flags & PX_FORMAT_FLAG_LEADING_ZERO) == 0) {
        pxint32 unicode = string.memory[index];

        if (string.length > index + 1 && unicode == PX_ASCII_ZERO)
            return 0;
    }

    for (; index < string.length; index += 1) {
        pxword8 digit = pxAsciiDigitValue(string.memory[index], radix);

        if (digit < 0 || digit >= radix) return 0;

        if (temp > (PX_WORD_MAX - digit) / radix)
            return 0;

        temp = temp * radix + digit;
    }

    if (self != 0) *self = temp;

    return 1;
}

#endif // PX_FORMAT_STRING8_C
