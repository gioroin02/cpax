#ifndef PX_STRING_UNICODE_C
#define PX_STRING_UNICODE_C

#include "unicode.h"

pxbool8
pxUnicodeIsValid(pxint32 value)
{
    if (value >= 0x0 && value <= 0xd7ff)
        return 1;

    if (value >= 0xe000 && value <= 0x10ffff)
        return 1;

    return 0;
}

pxbool8
pxUnicodeIsSurrogate(pxint32 value)
{
    if (value >= 0xd800 && value <= 0xdfff)
        return 1;

    return 0;
}

pxbool8
pxUnicodeIsSurrogateLow(pxint32 value)
{
    if (value >= 0xdc00 && value <= 0xdfff)
        return 1;

    return 0;
}

pxbool8
pxUnicodeIsSurrogateHigh(pxint32 value)
{
    if (value >= 0xd800 && value <= 0xdbff)
        return 1;

    return 0;
}

pxbool8
pxUnicodeIsAscii(pxint32 value)
{
    return value < 128 ? 1 : 0;
}

pxbool8
pxAsciiIsSpace(pxint32 value)
{
    switch (value) {
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
        case 32:
            return 1;

        default: break;
    }

    return 0;
}

pxword
pxAsciiDigitValue(pxint32 value, pxword radix)
{
    switch (value) {
        case 48:
        case 49:
        case 50:
        case 51:
        case 52:
        case 53:
        case 54:
        case 55:
        case 56:
        case 57: {
            pxword result = value - 48;

            if (radix >= 2 && radix <= 16 && result < radix)
                return result;
        } break;

        case 65:
        case 66:
        case 67:
        case 68:
        case 69:
        case 70: {
            pxword result = value - 55;

            if (radix >= 11 && radix <= 16 && result < radix)
                return result;
        } break;

        case 97:
        case 98:
        case 99:
        case 100:
        case 101:
        case 102: {
            pxword result = value - 87;

            if (radix >= 11 && radix <= 16 && result < radix)
                return result;
        } break;

        default: break;
    }

    return radix;
}

#endif // PX_STRING_UNICODE_C
