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

#endif // PX_STRING_UNICODE_C
