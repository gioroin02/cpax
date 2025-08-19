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
    if (value >= 0x0 && value <= 0x7f)
        return 1;

    return 0;
}

pxb8
pxAsciiIsSpace(pxi32 value)
{
    switch (value) {
        case PX_ASCII_HORIZONTAL_TAB:
        case PX_ASCII_LINE_FEED:
        case PX_ASCII_VERTICAL_TAB:
        case PX_ASCII_PAGE_FEED:
        case PX_ASCII_CARRIAGE_RETURN:
        case PX_ASCII_SPACE:
            return 1;

        default: break;
    }

    return 0;
}

pxb8
pxAsciiIsNumeric(pxi32 value, pxunsig radix)
{
    switch (value) {
        case PX_ASCII_PLUS:
        case PX_ASCII_MINUS:
        case PX_ASCII_POINT:
        case PX_ASCII_UPPER_E:
        case PX_ASCII_LOWER_E:
            return 1;

        default: break;
    }

    return pxAsciiIsDigit(value, radix);
}

pxb8
pxAsciiIsDigit(pxi32 value, pxunsig radix)
{
    pxunsig temp = 0;

    switch (value) {
        case PX_ASCII_ZERO:
        case PX_ASCII_ONE:
        case PX_ASCII_TWO:
        case PX_ASCII_THREE:
        case PX_ASCII_FOUR:
        case PX_ASCII_FIVE:
        case PX_ASCII_SIX:
        case PX_ASCII_SEVEN:
        case PX_ASCII_EIGHT:
        case PX_ASCII_NINE:
            temp = value - PX_ASCII_ZERO;

            if (radix >= 2 && radix <= 16 && temp < radix)
                return 1;
        break;

        case PX_ASCII_UPPER_A:
        case PX_ASCII_UPPER_B:
        case PX_ASCII_UPPER_C:
        case PX_ASCII_UPPER_D:
        case PX_ASCII_UPPER_E:
        case PX_ASCII_UPPER_F:
            temp = value - PX_ASCII_UPPER_A - 10;

            if (radix >= 11 && radix <= 16 && temp < radix)
                return 1;
        break;

        case PX_ASCII_LOWER_A:
        case PX_ASCII_LOWER_B:
        case PX_ASCII_LOWER_C:
        case PX_ASCII_LOWER_D:
        case PX_ASCII_LOWER_E:
        case PX_ASCII_LOWER_F:
            temp = value - PX_ASCII_LOWER_A - 10;

            if (radix >= 11 && radix <= 16 && temp < radix)
                return 1;
        break;

        default: break;
    }

    return 0;
}

pxb8
pxAsciiIsLetter(pxi32 value)
{
    if (value >= PX_ASCII_UPPER_A && value <= PX_ASCII_UPPER_Z)
        return 1;

    if (value >= PX_ASCII_LOWER_A && value <= PX_ASCII_LOWER_Z)
        return 1;

    return 0;
}

pxb8
pxAsciiIsLetterUpper(pxi32 value)
{
    if (value >= PX_ASCII_UPPER_A && value <= PX_ASCII_UPPER_Z)
        return 1;

    return 0;
}

pxb8
pxAsciiIsLetterLower(pxi32 value)
{
    if (value >= PX_ASCII_LOWER_A && value <= PX_ASCII_LOWER_Z)
        return 1;

    return 0;
}

pxunsig
pxAsciiDigitValue(pxi32 value, pxunsig radix)
{
    pxunsig result = radix;
    pxunsig temp   = 0;

    switch (value) {
        case PX_ASCII_ZERO:
        case PX_ASCII_ONE:
        case PX_ASCII_TWO:
        case PX_ASCII_THREE:
        case PX_ASCII_FOUR:
        case PX_ASCII_FIVE:
        case PX_ASCII_SIX:
        case PX_ASCII_SEVEN:
        case PX_ASCII_EIGHT:
        case PX_ASCII_NINE:
            temp = value - PX_ASCII_ZERO;

            if (radix >= 2 && radix <= 16 && temp < radix)
                result = temp;
        break;

        case PX_ASCII_UPPER_A:
        case PX_ASCII_UPPER_B:
        case PX_ASCII_UPPER_C:
        case PX_ASCII_UPPER_D:
        case PX_ASCII_UPPER_E:
        case PX_ASCII_UPPER_F:
            temp = value - PX_ASCII_UPPER_A - 10;

            if (radix >= 11 && radix <= 16 && temp < radix)
                result = temp;
        break;

        case PX_ASCII_LOWER_A:
        case PX_ASCII_LOWER_B:
        case PX_ASCII_LOWER_C:
        case PX_ASCII_LOWER_D:
        case PX_ASCII_LOWER_E:
        case PX_ASCII_LOWER_F:
            temp = value - PX_ASCII_LOWER_A - 10;

            if (radix >= 11 && radix <= 16 && temp < radix)
                result = temp;
        break;

        default: break;
    }

    return result;
}

#endif // PX_STRING_UNICODE_C
