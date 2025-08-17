#ifndef PX_STRING_STRING16_C
#define PX_STRING_STRING16_C

#include "string16.h"

PxString16
pxString16FromUnicode(PxArena* arena, pxint32 value)
{
    pxint    length = pxUtf16UnitsToWrite(value);
    pxword16* result = pxArenaReserve(arena, pxword16, length + 1);

    if (result == 0 || length <= 0)
        return (PxString16) {0};

    pxUtf16WriteMemoryForw(result, length, 0, value);

    return (PxString16) {
        .memory = result,
        .length = length,
    };
}

PxString16
pxString16Copy(PxArena* arena, PxString16 string)
{
    return pxString16CopyMemory(arena, string.memory, string.length);
}

PxString16
pxString16CopyMemory(PxArena* arena, pxword16* memory, pxint length)
{
    pxword16* result = pxArenaReserve(arena, pxword16, length + 1);

    if (result == 0 || length <= 0)
        return (PxString16) {0};

    pxMemoryCopy(result, memory, length, 2);

    return (PxString16) {
        .memory = result,
        .length = length,
    };
}

PxString16
pxString16Chain(PxString16 self, PxArena* arena, PxString16 value)
{
    return pxString16ChainMemory(self, arena, value.memory, value.length);
}

PxString16
pxString16ChainMemory(PxString16 self, PxArena* arena, pxword16* memory, pxint length)
{
    pxword16* result = pxArenaReserve(arena,
        pxword16, self.length + length + 1);

    if (result == 0) return (PxString16) {0};

    pxMemoryCopy(result, self.memory, self.length, 2);
    pxMemoryCopy(result + self.length, memory, length, 2);

    return (PxString16) {
        .memory = result,
        .length = length,
    };
}

pxbool16
pxString16Get(PxString16 self, pxint index, pxword16* value)
{
    if (index < 0 || index >= self.length)
        return 0;

    if (value != 0)
        *value = self.memory[index];

    return 1;
}

pxword16
pxString16GetOr(PxString16 self, pxint index, pxword16 value)
{
    if (index < 0 || index >= self.length)
        return value;

    return self.memory[index];
}

pxbool16
pxString16IsEqual(PxString16 self, PxString16 value)
{
    return pxString16IsEqualMemory(self, value.memory, value.length);
}

pxbool16
pxString16IsEqualMemory(PxString16 self, pxword16* memory, pxint length)
{
    if (self.length == length)
        return pxMemoryIsEqual(self.memory, memory, length, 1);

    return 0;
}

pxbool16
pxString16BeginsWith(PxString16 self, PxString16 value)
{
    return pxString16BeginsWithMemory(self, value.memory, value.length);
}

pxbool16
pxString16BeginsWithMemory(PxString16 self, pxword16* memory, pxint length)
{
    PxString16 slice =
        pxString16SliceLength(self, 0, length);

    return pxString16IsEqualMemory(slice, memory, length);
}

pxbool16
pxString16EndsWith(PxString16 self, PxString16 value)
{
    return pxString16EndsWithMemory(self, value.memory, value.length);
}

pxbool16
pxString16EndsWithMemory(PxString16 self, pxword16* memory, pxint length)
{
    PxString16 slice =
        pxString16SliceLength(self, self.length - length, length);

    return pxString16IsEqualMemory(slice, memory, length);
}

pxint
pxString16Contains(PxString16 self, PxString16 value)
{
    return pxString16ContainsMemory(self, value.memory, value.length);
}

pxint
pxString16ContainsMemory(PxString16 self, pxword16* memory, pxint length)
{
    pxint result = 0;

    if (self.length < length) return result;

    for (pxint i = 0; i < self.length - length; i += 1) {
        PxString16 slice = pxString16SliceLength(self, i, length);

        if (pxString16IsEqualMemory(slice, memory, length) != 0)
            result += 1, i += length;
    }

    return result;
}

PxString16
pxString16Slice(PxString16 self, pxint start, pxint stop)
{
    return pxString16SliceLength(self, start, stop - start);
}

PxString16
pxString16SliceLength(PxString16 self, pxint index, pxint length)
{
    if (length <= 0) return (PxString16) {0};

    if (index < 0 || index + length > self.length)
        return (PxString16) {0};

    pxword16* memory = self.memory + index;

    return (PxString16) {
        .memory = memory,
        .length = length,
    };
}

PxString16
pxString16TrimSpaces(PxString16 self)
{
    pxint units = 0;
    pxint start = 0;
    pxint stop  = self.length;

    for (; start < stop; start += units) {
        pxint32 unicode = 0;

        units = pxUtf16ReadMemoryForw(self.memory,
            self.length, start, &unicode);

        if (units <= 0) return (PxString16) {0};

        if (pxAsciiIsSpace(unicode) == 0)
            break;
    }

    for (; start < stop; stop -= units) {
        pxint32 unicode = 0;

        units = pxUtf16ReadMemoryBack(self.memory,
            self.length, stop - 1, &unicode);

        if (units <= 0) return (PxString16) {0};

        if (pxAsciiIsSpace(unicode) == 0)
            break;
    }

    return pxString16Slice(self, start, stop);
}

PxString16
pxString16TrimSpacesHead(PxString16 self)
{
    pxint units = 0;
    pxint start = 0;
    pxint stop  = self.length;

    for (; start < stop; start += units) {
        pxint32 unicode = 0;

        units = pxUtf16ReadMemoryForw(self.memory,
            self.length, start, &unicode);

        if (units <= 0) return (PxString16) {0};

        if (pxAsciiIsSpace(unicode) == 0)
            break;
    }

    return pxString16Slice(self, start, stop);
}

PxString16
pxString16TrimSpacesTail(PxString16 self)
{
    pxint units = 0;
    pxint start = 0;
    pxint stop  = self.length;

    for (; start < stop; stop -= units) {
        pxint32 unicode = 0;

        units = pxUtf16ReadMemoryBack(self.memory,
            self.length, stop - 1, &unicode);

        if (units <= 0) return (PxString16) {0};

        if (pxAsciiIsSpace(unicode) == 0)
            break;
    }

    return pxString16Slice(self, start, stop);
}

PxString16
pxString16TrimPrefix(PxString16 self, PxString16 prefix)
{
    if (pxString16BeginsWith(self, prefix) != 0)
        return pxString16Slice(self, prefix.length, self.length);

    return pxString16SliceLength(self, 0, self.length);
}

PxString16
pxString16TrimPrefixMemory(PxString16 self, pxword16* memory, pxint length)
{
    if (pxString16BeginsWithMemory(self, memory, length) != 0)
        return pxString16Slice(self, length, self.length);

    return pxString16SliceLength(self, 0, self.length);
}

PxString16
pxString16TrimSuffix(PxString16 self, PxString16 suffix)
{
    if (pxString16EndsWith(self, suffix) != 0)
        return pxString16Slice(self, 0, self.length - suffix.length);

    return pxString16SliceLength(self, 0, self.length);
}

PxString16
pxString16TrimSuffixMemory(PxString16 self, pxword16* memory, pxint length)
{
    if (pxString16EndsWithMemory(self, memory, length) != 0)
        return pxString16Slice(self, 0, self.length - length);

    return pxString16SliceLength(self, 0, self.length);
}

pxbool16
pxString16FindFirst(PxString16 self, pxint start, PxString16 value, pxint* index)
{
    return pxString16FindFirstMemory(self, start, value.memory, value.length, index);
}

pxbool16
pxString16FindFirstMemory(PxString16 self, pxint start, pxword16* memory, pxint length, pxint* index)
{
    start = pxClamp(start, 0, self.length);

    for (pxint i = start; i < self.length; i += 1) {
        PxString16 slice = pxString16SliceLength(self, i, length);

        if (pxString16IsEqualMemory(slice, memory, length) == 0)
            continue;

        if (index != 0) *index = i;

        return 1;
    }

    return 0;
}

pxbool16
pxString16FindLast(PxString16 self, pxint start, PxString16 value, pxint* index)
{
    return pxString16FindLastMemory(self, start, value.memory, value.length, index);
}

pxbool16
pxString16FindLastMemory(PxString16 self, pxint start, pxword16* memory, pxint length, pxint* index)
{
    start = pxClamp(start, 0, self.length);

    for (pxint i = start; i > 0; i -= 1) {
        PxString16 slice = pxString16SliceLength(self, i - length, length);

        if (pxString16IsEqualMemory(slice, memory, length) == 0)
            continue;

        if (index != 0) *index = i - length;

        return 1;
    }

    return 0;
}

pxbool16
pxString16Split(PxString16 self, PxString16 pivot, PxString16* left, PxString16* right)
{
    return pxString16SplitMemory(self, pivot.memory, pivot.length, left, right);
}

pxbool16
pxString16SplitMemory(PxString16 self, pxword16* memory, pxint length, PxString16* left, PxString16* right)
{
    pxint start = 0;
    pxint stop  = self.length;
    pxint index = self.length;

    if (pxString16FindFirstMemory(self, start, memory, length, &index) == 0)
        return 0;

    if (left != 0) *left = pxString16Slice(self, start, index);

    if (right != 0)
        *right = pxString16Slice(self, index + length, stop);

    return 1;
}

pxbool16
pxString16Next(PxString16 self, pxint index, pxint* units, pxint32* value)
{
    if (index < 0 || index >= self.length)
        return 0;

    pxint step = pxUtf16ReadMemoryForw(self.memory,
        self.length, index, value);

    if (step == 0) return 0;

    if (units != 0) *units = step;

    return 1;
}

pxbool16
pxString16Prev(PxString16 self, pxint index, pxint* units, pxint32* value)
{
    if (index < 0 || index >= self.length)
        return 0;

    pxint step = pxUtf16ReadMemoryBack(self.memory,
        self.length, index, value);

    if (step == 0) return 0;

    if (units != 0) *units = step;

    return 1;
}

#endif // PX_STRING_STRING16_C
