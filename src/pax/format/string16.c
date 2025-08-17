#ifndef PX_FORMAT_STRING16_C
#define PX_FORMAT_STRING16_C

#include "string8.h"

pxbool8
pxWord8FromString16(pxword8* self, PxFormatOptions options, PxString16 string)
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
pxWord16FromString16(pxword16* self, PxFormatOptions options, PxString16 string)
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
pxWord32FromString16(pxword32* self, PxFormatOptions options, PxString16 string)
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
pxWord64FromString16(pxword64* self, PxFormatOptions options, PxString16 string)
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
pxWordFromString16(pxword* self, PxFormatOptions options, PxString16 string)
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

pxbool8
pxInt8FromString16(pxint8* self, PxFormatOptions options, PxString16 string)
{
    PxFormatFlag flags = options.flags;
    pxint8       radix = options.radix;
    pxint        index = 0;
    pxint8       temp  = 0;
    pxbool8      sign  = 0;

    if (string.length <= 0) return 0;

    switch (string.memory[index]) {
        case PX_ASCII_PLUS:
            if ((flags & PX_FORMAT_FLAG_LEADING_PLUS) == 0)
                return 0;

            index += 1;
        break;

        case PX_ASCII_MINUS:
            index += 1;
            sign   = 1;
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

        switch (sign) {
            case 0:
                if (temp > (PX_INT8_MAX - digit) / radix)
                    return 0;

                temp = temp * radix + digit;
            break;

            case 1:
                if (temp < (PX_INT8_MIN + digit) / radix)
                    return 0;

                temp = temp * radix - digit;
            break;

            default: return 0;
        }
    }

    if (self != 0) *self = temp;

    return 1;
}

pxbool8
pxInt16FromString16(pxint16* self, PxFormatOptions options, PxString16 string)
{
    PxFormatFlag flags = options.flags;
    pxint8       radix = options.radix;
    pxint        index = 0;
    pxint16      temp  = 0;
    pxbool8      sign  = 0;

    if (string.length <= 0) return 0;

    switch (string.memory[index]) {
        case PX_ASCII_PLUS:
            if ((flags & PX_FORMAT_FLAG_LEADING_PLUS) == 0)
                return 0;

            index += 1;
        break;

        case PX_ASCII_MINUS:
            index += 1;
            sign   = 1;
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

        switch (sign) {
            case 0:
                if (temp > (PX_INT16_MAX - digit) / radix)
                    return 0;

                temp = temp * radix + digit;
            break;

            case 1:
                if (temp < (PX_INT16_MIN + digit) / radix)
                    return 0;

                temp = temp * radix - digit;
            break;

            default: return 0;
        }
    }

    if (self != 0) *self = temp;

    return 1;
}

pxbool8
pxInt32FromString16(pxint32* self, PxFormatOptions options, PxString16 string)
{
    PxFormatFlag flags = options.flags;
    pxint8       radix = options.radix;
    pxint        index = 0;
    pxint32      temp  = 0;
    pxbool8      sign  = 0;

    if (string.length <= 0) return 0;

    switch (string.memory[index]) {
        case PX_ASCII_PLUS:
            if ((flags & PX_FORMAT_FLAG_LEADING_PLUS) == 0)
                return 0;

            index += 1;
        break;

        case PX_ASCII_MINUS:
            index += 1;
            sign   = 1;
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

        switch (sign) {
            case 0:
                if (temp > (PX_INT32_MAX - digit) / radix)
                    return 0;

                temp = temp * radix + digit;
            break;

            case 1:
                if (temp < (PX_INT32_MIN + digit) / radix)
                    return 0;

                temp = temp * radix - digit;
            break;

            default: return 0;
        }
    }

    if (self != 0) *self = temp;

    return 1;
}

pxbool8
pxInt64FromString16(pxint64* self, PxFormatOptions options, PxString16 string)
{
    PxFormatFlag flags = options.flags;
    pxint8       radix = options.radix;
    pxint        index = 0;
    pxint64      temp  = 0;
    pxbool8      sign  = 0;

    if (string.length <= 0) return 0;

    switch (string.memory[index]) {
        case PX_ASCII_PLUS:
            if ((flags & PX_FORMAT_FLAG_LEADING_PLUS) == 0)
                return 0;

            index += 1;
        break;

        case PX_ASCII_MINUS:
            index += 1;
            sign   = 1;
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

        switch (sign) {
            case 0:
                if (temp > (PX_INT64_MAX - digit) / radix)
                    return 0;

                temp = temp * radix + digit;
            break;

            case 1:
                if (temp < (PX_INT64_MIN + digit) / radix)
                    return 0;

                temp = temp * radix - digit;
            break;

            default: return 0;
        }
    }

    if (self != 0) *self = temp;

    return 1;
}

pxbool8
pxIntFromString16(pxint* self, PxFormatOptions options, PxString16 string)
{
    PxFormatFlag flags = options.flags;
    pxint8       radix = options.radix;
    pxint        index = 0;
    pxint        temp  = 0;
    pxbool8      sign  = 0;

    if (string.length <= 0) return 0;

    switch (string.memory[index]) {
        case PX_ASCII_PLUS:
            if ((flags & PX_FORMAT_FLAG_LEADING_PLUS) == 0)
                return 0;

            index += 1;
        break;

        case PX_ASCII_MINUS:
            index += 1;
            sign   = 1;
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

        switch (sign) {
            case 0:
                if (temp > (PX_INT_MAX - digit) / radix)
                    return 0;

                temp = temp * radix + digit;
            break;

            case 1:
                if (temp < (PX_INT_MIN + digit) / radix)
                    return 0;

                temp = temp * radix - digit;
            break;

            default: return 0;
        }
    }

    if (self != 0) *self = temp;

    return 1;
}

#endif // PX_FORMAT_STRING16_C
