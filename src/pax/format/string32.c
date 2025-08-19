#ifndef PX_FORMAT_STRING32_C
#define PX_FORMAT_STRING32_C

#include "string8.h"

pxb8
pxUnsig8FromString32(pxu8* self, PxFormatOptions options, PxString32 string)
{
    PxFormatFlag flags = options.flags;
    pxu8         radix = options.radix;
    pxint        index = 0;
    pxu8         temp  = 0;

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
        pxi32 unicode = string.memory[index];

        if (string.length > index + 1 && unicode == PX_ASCII_ZERO)
            return 0;
    }

    for (; index < string.length; index += 1) {
        pxu8 digit = pxAsciiDigitValue(string.memory[index], radix);

        if (digit < 0 || digit >= radix) return 0;

        if (temp > (PX_U8_MAX - digit) / radix)
            return 0;

        temp = temp * radix + digit;
    }

    if (self != 0) *self = temp;

    return 1;
}

pxb8
pxUnsig16FromString32(pxu16* self, PxFormatOptions options, PxString32 string)
{
    PxFormatFlag flags = options.flags;
    pxu8         radix = options.radix;
    pxint        index = 0;
    pxu16        temp  = 0;

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
        pxi32 unicode = string.memory[index];

        if (string.length > index + 1 && unicode == PX_ASCII_ZERO)
            return 0;
    }

    for (; index < string.length; index += 1) {
        pxu8 digit = pxAsciiDigitValue(string.memory[index], radix);

        if (digit < 0 || digit >= radix) return 0;

        if (temp > (PX_U16_MAX - digit) / radix)
            return 0;

        temp = temp * radix + digit;
    }

    if (self != 0) *self = temp;

    return 1;
}

pxb8
pxUnsig32FromString32(pxu32* self, PxFormatOptions options, PxString32 string)
{
    PxFormatFlag flags = options.flags;
    pxu8         radix = options.radix;
    pxint        index = 0;
    pxu32        temp  = 0;

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
        pxi32 unicode = string.memory[index];

        if (string.length > index + 1 && unicode == PX_ASCII_ZERO)
            return 0;
    }

    for (; index < string.length; index += 1) {
        pxu8 digit = pxAsciiDigitValue(string.memory[index], radix);

        if (digit < 0 || digit >= radix) return 0;

        if (temp > (PX_U32_MAX - digit) / radix)
            return 0;

        temp = temp * radix + digit;
    }

    if (self != 0) *self = temp;

    return 1;
}

pxb8
pxUnsig64FromString32(pxu64* self, PxFormatOptions options, PxString32 string)
{
    PxFormatFlag flags = options.flags;
    pxu8         radix = options.radix;
    pxint        index = 0;
    pxu64        temp  = 0;

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
        pxi32 unicode = string.memory[index];

        if (string.length > index + 1 && unicode == PX_ASCII_ZERO)
            return 0;
    }

    for (; index < string.length; index += 1) {
        pxu8 digit = pxAsciiDigitValue(string.memory[index], radix);

        if (digit < 0 || digit >= radix) return 0;

        if (temp > (PX_U64_MAX - digit) / radix)
            return 0;

        temp = temp * radix + digit;
    }

    if (self != 0) *self = temp;

    return 1;
}

pxb8
pxUnsigFromString32(pxunsig* self, PxFormatOptions options, PxString32 string)
{
    PxFormatFlag flags = options.flags;
    pxu8         radix = options.radix;
    pxint        index = 0;
    pxunsig      temp  = 0;

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
        pxi32 unicode = string.memory[index];

        if (string.length > index + 1 && unicode == PX_ASCII_ZERO)
            return 0;
    }

    for (; index < string.length; index += 1) {
        pxu8 digit = pxAsciiDigitValue(string.memory[index], radix);

        if (digit < 0 || digit >= radix) return 0;

        if (temp > (PX_UNSIG_MAX - digit) / radix)
            return 0;

        temp = temp * radix + digit;
    }

    if (self != 0) *self = temp;

    return 1;
}

pxb8
pxInt8FromString32(pxi8* self, PxFormatOptions options, PxString32 string)
{
    PxFormatFlag flags = options.flags;
    pxi8         radix = options.radix;
    pxint        index = 0;
    pxi8         temp  = 0;
    pxb8         sign  = 0;

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
        pxi32 unicode = string.memory[index];

        if (string.length > index + 1 && unicode == PX_ASCII_ZERO)
            return 0;
    }

    for (; index < string.length; index += 1) {
        pxu8 digit = pxAsciiDigitValue(string.memory[index], radix);

        if (digit < 0 || digit >= radix) return 0;

        switch (sign) {
            case 0:
                if (temp > (PX_I8_MAX - digit) / radix)
                    return 0;

                temp = temp * radix + digit;
            break;

            case 1:
                if (temp < (PX_I8_MIN + digit) / radix)
                    return 0;

                temp = temp * radix - digit;
            break;

            default: return 0;
        }
    }

    if (self != 0) *self = temp;

    return 1;
}

pxb8
pxInt16FromString32(pxi16* self, PxFormatOptions options, PxString32 string)
{
    PxFormatFlag flags = options.flags;
    pxi8         radix = options.radix;
    pxint        index = 0;
    pxi16        temp  = 0;
    pxb8         sign  = 0;

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
        pxi32 unicode = string.memory[index];

        if (string.length > index + 1 && unicode == PX_ASCII_ZERO)
            return 0;
    }

    for (; index < string.length; index += 1) {
        pxu8 digit = pxAsciiDigitValue(string.memory[index], radix);

        if (digit < 0 || digit >= radix) return 0;

        switch (sign) {
            case 0:
                if (temp > (PX_I16_MAX - digit) / radix)
                    return 0;

                temp = temp * radix + digit;
            break;

            case 1:
                if (temp < (PX_I16_MIN + digit) / radix)
                    return 0;

                temp = temp * radix - digit;
            break;

            default: return 0;
        }
    }

    if (self != 0) *self = temp;

    return 1;
}

pxb8
pxInt32FromString32(pxi32* self, PxFormatOptions options, PxString32 string)
{
    PxFormatFlag flags = options.flags;
    pxi8         radix = options.radix;
    pxint        index = 0;
    pxi32        temp  = 0;
    pxb8         sign  = 0;

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
        pxi32 unicode = string.memory[index];

        if (string.length > index + 1 && unicode == PX_ASCII_ZERO)
            return 0;
    }

    for (; index < string.length; index += 1) {
        pxu8 digit = pxAsciiDigitValue(string.memory[index], radix);

        if (digit < 0 || digit >= radix) return 0;

        switch (sign) {
            case 0:
                if (temp > (PX_I32_MAX - digit) / radix)
                    return 0;

                temp = temp * radix + digit;
            break;

            case 1:
                if (temp < (PX_I32_MIN + digit) / radix)
                    return 0;

                temp = temp * radix - digit;
            break;

            default: return 0;
        }
    }

    if (self != 0) *self = temp;

    return 1;
}

pxb8
pxInt64FromString32(pxi64* self, PxFormatOptions options, PxString32 string)
{
    PxFormatFlag flags = options.flags;
    pxi8         radix = options.radix;
    pxint        index = 0;
    pxi64        temp  = 0;
    pxb8         sign  = 0;

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
        pxi32 unicode = string.memory[index];

        if (string.length > index + 1 && unicode == PX_ASCII_ZERO)
            return 0;
    }

    for (; index < string.length; index += 1) {
        pxu8 digit = pxAsciiDigitValue(string.memory[index], radix);

        if (digit < 0 || digit >= radix) return 0;

        switch (sign) {
            case 0:
                if (temp > (PX_I64_MAX - digit) / radix)
                    return 0;

                temp = temp * radix + digit;
            break;

            case 1:
                if (temp < (PX_I64_MIN + digit) / radix)
                    return 0;

                temp = temp * radix - digit;
            break;

            default: return 0;
        }
    }

    if (self != 0) *self = temp;

    return 1;
}

pxb8
pxIntFromString32(pxint* self, PxFormatOptions options, PxString32 string)
{
    PxFormatFlag flags = options.flags;
    pxi8         radix = options.radix;
    pxint        index = 0;
    pxint        temp  = 0;
    pxb8         sign  = 0;

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
        pxi32 unicode = string.memory[index];

        if (string.length > index + 1 && unicode == PX_ASCII_ZERO)
            return 0;
    }

    for (; index < string.length; index += 1) {
        pxu8 digit = pxAsciiDigitValue(string.memory[index], radix);

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

#endif // PX_FORMAT_STRING32_C
