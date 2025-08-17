#ifndef PX_STRING_UTF16_C
#define PX_STRING_UTF16_C

#include "utf16.h"

pxbool16
pxUtf16Encode(PxUtf16* self, pxint32 value)
{
    pxint units = pxUtf16UnitsToWrite(value);

    pxMemoryZero(self->memory, PX_UTF16_MAX_UNITS, 2);

    self->size = 0;

    switch (units) {
        case 1: self->a = pxCast(pxword16, value); break;

        case 2:
            pxint32 temp = value - 0x10000;

            self->a = pxCast(pxword16, ((value >> 10) & 0xffff) | 0xd800);
            self->b = pxCast(pxword16, ((value >>  0) & 0x03ff) | 0xdc00);
        break;

        default: return 0;
    }

    self->size = units;

    return 1;
}

pxint
pxUtf16WriteMemoryForw(pxword16* memory, pxint length, pxint index, pxint32 value)
{
    PxUtf16 utf16 = {0};

    if (pxUtf16Encode(&utf16, value) == 0) return 0;

    if (index < 0 || index + utf16.size > length)
        return 0;

    for (pxint i = 0; i < utf16.size; i += 1)
        memory[index + i] = utf16.memory[i];

    return utf16.size;
}

pxint
pxUtf16WriteMemoryBack(pxword16* memory, pxint length, pxint index, pxint32 value)
{
    PxUtf16 utf16 = {0};

    if (pxUtf16Encode(&utf16, value) == 0) return 0;

    if (index - utf16.size < 0 || index >= length)
        return 0;

    for (pxint i = 0; i < utf16.size; i += 1)
        memory[index - utf16.size + i] = utf16.memory[i];

    return utf16.size;
}

pxbool8
pxUtf16Decode(PxUtf16* self, pxint32* value)
{
    pxint   units = pxUtf16UnitsToRead(self->memory[0]);
    pxint32 temp  = 0;

    if (self->size != units) return 0;

    switch (units) {
        case 1: temp = self->a; break;

        case 2:
            if (pxUnicodeIsSurrogateHigh(self->b) == 0)
                return 0;

            temp  = 0x10000;
            temp += (self->a - 0xd800) << 10;
            temp += (self->b - 0xdc00) <<  0;
        break;

        default: return 0;
    }

    if (pxUnicodeIsValid(temp) == 0) return 0;

    if (value != 0) *value = temp;

    return 1;
}

pxint
pxUtf16ReadMemoryForw(pxword16* memory, pxint length, pxint index, pxint32* value)
{
    PxUtf16 utf16 = {0};

    if (index >= 0 && index < length)
        utf16.size = pxUtf16UnitsToRead(memory[index]);

    if (utf16.size <= 0 || index + utf16.size > length)
        return 0;

    for (pxint i = 0; i < utf16.size; i += 1)
        utf16.memory[i] = memory[index + i];

    if (pxUtf16Decode(&utf16, value) == 0) return 0;

    return utf16.size;
}

pxint
pxUtf16ReadMemoryBack(pxword16* memory, pxint length, pxint index, pxint32* value)
{
    PxUtf16 utf16 = {0};
    pxint   start = index;

    if (index < 0 || index >= length) return 0;

    while (pxUnicodeIsSurrogateLow(memory[index]) != 0) {
        index -= 1;

        if (index < 0 || index >= length)
            return 0;
    }

    utf16.size = start - index + 1;

    if (utf16.size != pxUtf16UnitsToRead(memory[index]))
        return 0;

    for (pxint i = 0; i < utf16.size; i += 1)
        utf16.memory[i] = memory[index + i];

    if (pxUtf16Decode(&utf16, value) == 0) return 0;

    return utf16.size;
}

pxint
pxUtf16UnitsToWrite(pxint32 value)
{
    if (value >=     0x0 && value <=   0xd7ff) return 1;
    if (value >=  0xe000 && value <=   0xffff) return 1;
    if (value >= 0x10000 && value <= 0x10ffff) return 2;

    return 0;
}

pxint
pxUtf16UnitsToRead(pxword16 value)
{
    if (value >=    0x0 && value <= 0xd7ff) return 1;
    if (value >= 0xd800 && value <= 0xdbff) return 2;
    if (value >= 0xe000 && value <= 0xffff) return 1;

    return 0;
}

#endif // PX_STRING_UTF16_C
