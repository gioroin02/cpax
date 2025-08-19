#ifndef PX_STRING_UNICODE_C
#define PX_STRING_UNICODE_C

#include "unicode.h"

pxb8
pxUnicodeIsValid(pxi32 value)
{
    if (value >= 0x0 && value <= 0xd7ff)
        return 1;

    if (value >= 0xe000 && value <= 0x10ffff)
        return 1;

    return 0;
}

pxb8
pxUnicodeIsSurrogate(pxi32 value)
{
    if (value >= 0xd800 && value <= 0xdfff)
        return 1;

    return 0;
}

pxb8
pxUnicodeIsSurrogateLow(pxi32 value)
{
    if (value >= 0xdc00 && value <= 0xdfff)
        return 1;

    return 0;
}

pxb8
pxUnicodeIsSurrogateHigh(pxi32 value)
{
    if (value >= 0xd800 && value <= 0xdbff)
        return 1;

    return 0;
}

pxb8
pxUnicodeIsAscii(pxi32 value)
{
    return value < 128 ? 1 : 0;
}

pxb8
pxAsciiIsSpace(pxi32 value)
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

pxunsig
pxAsciiDigitValue(pxi32 value, pxunsig radix)
{
    pxunsig result = radix;
    pxunsig temp   = 0;

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
        case 57:
            temp = value - 48;

            if (radix >= 2 && radix <= 16 && temp < radix)
                result = temp;
        break;

        case 65:
        case 66:
        case 67:
        case 68:
        case 69:
        case 70:
            temp = value - 55;

            if (radix >= 11 && radix <= 16 && temp < radix)
                result = temp;
        break;

        case 97:
        case 98:
        case 99:
        case 100:
        case 101:
        case 102:
            temp = value - 87;

            if (radix >= 11 && radix <= 16 && temp < radix)
                result = temp;
        break;

        default: break;
    }

    return result;
}

#endif // PX_STRING_UNICODE_C
