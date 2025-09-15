#ifndef PX_CORE_FORMAT_MEMORY32_C
#define PX_CORE_FORMAT_MEMORY32_C

#include "memory32.h"

pxiword
pxMemory32WriteUnsigned8(pxu32* memory, pxiword length, pxuword radix, PxFormatFlag flags, pxu8 value)
{
    pxiword size = 0;
    pxu8    temp = value;

    if (temp != 0) {
        for (pxuword t = temp; t != 0; t /= radix)
            size += 1;
    } else
        size += 1;

    if ((flags & PX_FORMAT_FLAG_LEADING_PLUS) != 0)
        size += 1;

    if (size <= 0 || size > length) return 0;

    pxiword index = size;

    while (index > 0) {
        pxi32 digit = pxAsciiDigitFromValue(temp, radix,
            flags & PX_FORMAT_FLAG_UPPER_CASE);

        index -= 1;
        temp  /= radix;

        if (digit != PX_ASCII_NULL)
            memory[index] = pxCast(pxu16, digit);
        else
            return 0;
    }

    if ((flags & PX_FORMAT_FLAG_LEADING_PLUS) != 0)
        memory[index] = PX_ASCII_PLUS;

    return size;
}

pxiword
pxMemory32WriteUnsigned16(pxu32* memory, pxiword length, pxuword radix, PxFormatFlag flags, pxu16 value)
{
    pxiword size = 0;
    pxu16   temp = value;

    if (temp != 0) {
        for (pxuword t = temp; t != 0; t /= radix)
            size += 1;
    } else
        size += 1;

    if ((flags & PX_FORMAT_FLAG_LEADING_PLUS) != 0)
        size += 1;

    if (size <= 0 || size > length) return 0;

    pxiword index = size;

    while (index > 0) {
        pxi32 digit = pxAsciiDigitFromValue(temp, radix,
            flags & PX_FORMAT_FLAG_UPPER_CASE);

        index -= 1;
        temp  /= radix;

        if (digit != PX_ASCII_NULL)
            memory[index] = pxCast(pxu16, digit);
        else
            return 0;
    }

    if ((flags & PX_FORMAT_FLAG_LEADING_PLUS) != 0)
        memory[index] = PX_ASCII_PLUS;

    return size;
}

pxiword
pxMemory32WriteUnsigned32(pxu32* memory, pxiword length, pxuword radix, PxFormatFlag flags, pxu32 value)
{
    pxiword size = 0;
    pxu32   temp = value;

    if (temp != 0) {
        for (pxuword t = temp; t != 0; t /= radix)
            size += 1;
    } else
        size += 1;

    if ((flags & PX_FORMAT_FLAG_LEADING_PLUS) != 0)
        size += 1;

    if (size <= 0 || size > length) return 0;

    pxiword index = size;

    while (index > 0) {
        pxi32 digit = pxAsciiDigitFromValue(temp, radix,
            flags & PX_FORMAT_FLAG_UPPER_CASE);

        index -= 1;
        temp  /= radix;

        if (digit != PX_ASCII_NULL)
            memory[index] = pxCast(pxu16, digit);
        else
            return 0;
    }

    if ((flags & PX_FORMAT_FLAG_LEADING_PLUS) != 0)
        memory[index] = PX_ASCII_PLUS;

    return size;
}

pxiword
pxMemory32WriteUnsigned64(pxu32* memory, pxiword length, pxuword radix, PxFormatFlag flags, pxu64 value)
{
    pxiword size = 0;
    pxu64   temp = value;

    if (temp != 0) {
        for (pxuword t = temp; t != 0; t /= radix)
            size += 1;
    } else
        size += 1;

    if ((flags & PX_FORMAT_FLAG_LEADING_PLUS) != 0)
        size += 1;

    if (size <= 0 || size > length) return 0;

    pxiword index = size;

    while (index > 0) {
        pxi32 digit = pxAsciiDigitFromValue(temp, radix,
            flags & PX_FORMAT_FLAG_UPPER_CASE);

        index -= 1;
        temp  /= radix;

        if (digit != PX_ASCII_NULL)
            memory[index] = pxCast(pxu16, digit);
        else
            return 0;
    }

    if ((flags & PX_FORMAT_FLAG_LEADING_PLUS) != 0)
        memory[index] = PX_ASCII_PLUS;

    return size;
}

pxiword
pxMemory32WriteUnsigned(pxu32* memory, pxiword length, pxuword radix, PxFormatFlag flags, pxuword value)
{
    pxiword size = 0;
    pxuword temp = value;

    if (temp != 0) {
        for (pxuword t = temp; t != 0; t /= radix)
            size += 1;
    } else
        size += 1;

    if ((flags & PX_FORMAT_FLAG_LEADING_PLUS) != 0)
        size += 1;

    if (size <= 0 || size > length) return 0;

    pxiword index = size;

    while (index > 0) {
        pxi32 digit = pxAsciiDigitFromValue(temp, radix,
            flags & PX_FORMAT_FLAG_UPPER_CASE);

        index -= 1;
        temp  /= radix;

        if (digit != PX_ASCII_NULL)
            memory[index] = pxCast(pxu16, digit);
        else
            return 0;
    }

    if ((flags & PX_FORMAT_FLAG_LEADING_PLUS) != 0)
        memory[index] = PX_ASCII_PLUS;

    return size;
}

pxiword
pxMemory32WriteInteger8(pxu32* memory, pxiword length, pxuword radix, PxFormatFlag flags, pxi8 value)
{
    pxiword size = 0;
    pxu8    temp = pxMagnitudeInteger8(value);
    pxb8    sign = pxDirectionInteger8(value) < 0 ? 1 : 0;

    if (temp != 0) {
        for (pxuword t = temp; t != 0; t /= radix)
            size += 1;
    } else
        size += 1;

    if (sign != 0 || (flags & PX_FORMAT_FLAG_LEADING_PLUS) != 0)
        size += 1;

    if (size <= 0 || size > length) return 0;

    pxiword index = size;

    while (index > 0) {
        pxi32 digit = pxAsciiDigitFromValue(temp, radix,
            flags & PX_FORMAT_FLAG_UPPER_CASE);

        index -= 1;
        temp  /= radix;

        if (digit != PX_ASCII_NULL)
            memory[index] = pxCast(pxu16, digit);
        else
            return 0;
    }

    if (sign != 0) memory[index] = PX_ASCII_MINUS;

    if (sign == 0 && (flags & PX_FORMAT_FLAG_LEADING_PLUS) != 0)
        memory[index] = PX_ASCII_PLUS;

    return size;
}

pxiword
pxMemory32WriteInteger16(pxu32* memory, pxiword length, pxuword radix, PxFormatFlag flags, pxi16 value)
{
    pxiword size = 0;
    pxu16   temp = pxMagnitudeInteger16(value);
    pxb8    sign = pxDirectionInteger16(value) < 0 ? 1 : 0;

    if (temp != 0) {
        for (pxuword t = temp; t != 0; t /= radix)
            size += 1;
    } else
        size += 1;

    if (sign != 0 || (flags & PX_FORMAT_FLAG_LEADING_PLUS) != 0)
        size += 1;

    if (size <= 0 || size > length) return 0;

    pxiword index = size;

    while (index > 0) {
        pxi32 digit = pxAsciiDigitFromValue(temp, radix,
            flags & PX_FORMAT_FLAG_UPPER_CASE);

        index -= 1;
        temp  /= radix;

        if (digit != PX_ASCII_NULL)
            memory[index] = pxCast(pxu16, digit);
        else
            return 0;
    }

    if (sign != 0) memory[index] = PX_ASCII_MINUS;

    if (sign == 0 && (flags & PX_FORMAT_FLAG_LEADING_PLUS) != 0)
        memory[index] = PX_ASCII_PLUS;

    return size;
}

pxiword
pxMemory32WriteInteger32(pxu32* memory, pxiword length, pxuword radix, PxFormatFlag flags, pxi32 value)
{
    pxiword size = 0;
    pxu32   temp = pxMagnitudeInteger32(value);
    pxb8    sign = pxDirectionInteger32(value) < 0 ? 1 : 0;

    if (temp != 0) {
        for (pxuword t = temp; t != 0; t /= radix)
            size += 1;
    } else
        size += 1;

    if (sign != 0 || (flags & PX_FORMAT_FLAG_LEADING_PLUS) != 0)
        size += 1;

    if (size <= 0 || size > length) return 0;

    pxiword index = size;

    while (index > 0) {
        pxi32 digit = pxAsciiDigitFromValue(temp, radix,
            flags & PX_FORMAT_FLAG_UPPER_CASE);

        index -= 1;
        temp  /= radix;

        if (digit != PX_ASCII_NULL)
            memory[index] = pxCast(pxu16, digit);
        else
            return 0;
    }

    if (sign != 0) memory[index] = PX_ASCII_MINUS;

    if (sign == 0 && (flags & PX_FORMAT_FLAG_LEADING_PLUS) != 0)
        memory[index] = PX_ASCII_PLUS;

    return size;
}

pxiword
pxMemory32WriteInteger64(pxu32* memory, pxiword length, pxuword radix, PxFormatFlag flags, pxi64 value)
{
    pxiword size = 0;
    pxu64   temp = pxMagnitudeInteger64(value);
    pxb8    sign = pxDirectionInteger64(value) < 0 ? 1 : 0;

    if (temp != 0) {
        for (pxuword t = temp; t != 0; t /= radix)
            size += 1;
    } else
        size += 1;

    if (sign != 0 || (flags & PX_FORMAT_FLAG_LEADING_PLUS) != 0)
        size += 1;

    if (size <= 0 || size > length) return 0;

    pxiword index = size;

    while (index > 0) {
        pxi32 digit = pxAsciiDigitFromValue(temp, radix,
            flags & PX_FORMAT_FLAG_UPPER_CASE);

        index -= 1;
        temp  /= radix;

        if (digit != PX_ASCII_NULL)
            memory[index] = pxCast(pxu16, digit);
        else
            return 0;
    }

    if (sign != 0) memory[index] = PX_ASCII_MINUS;

    if (sign == 0 && (flags & PX_FORMAT_FLAG_LEADING_PLUS) != 0)
        memory[index] = PX_ASCII_PLUS;

    return size;
}

pxiword
pxMemory32WriteInteger(pxu32* memory, pxiword length, pxuword radix, PxFormatFlag flags, pxiword value)
{
    pxiword size = 0;
    pxuword temp = pxMagnitudeInteger(value);
    pxb8    sign = pxDirectionInteger(value) < 0 ? 1 : 0;

    if (temp != 0) {
        for (pxuword t = temp; t != 0; t /= radix)
            size += 1;
    } else
        size += 1;

    if (sign != 0 || (flags & PX_FORMAT_FLAG_LEADING_PLUS) != 0)
        size += 1;

    if (size <= 0 || size > length) return 0;

    pxiword index = size;

    while (index > 0) {
        pxi32 digit = pxAsciiDigitFromValue(temp, radix,
            flags & PX_FORMAT_FLAG_UPPER_CASE);

        index -= 1;
        temp  /= radix;

        if (digit != PX_ASCII_NULL)
            memory[index] = pxCast(pxu16, digit);
        else
            return 0;
    }

    if (sign != 0) memory[index] = PX_ASCII_MINUS;

    if (sign == 0 && (flags & PX_FORMAT_FLAG_LEADING_PLUS) != 0)
        memory[index] = PX_ASCII_PLUS;

    return size;
}

#endif // PX_CORE_FORMAT_MEMORY32_C
