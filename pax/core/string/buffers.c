#ifndef PX_CORE_STRING_BUFFERS_C
#define PX_CORE_STRING_BUFFERS_C

#include "buffers.h"

pxiword
pxBuffer8WriteMemory16Head(PxBuffer8* self, pxu16* memory, pxiword length)
{
    pxiword temp = pxUtf8UnitsFromMemory16(memory, length);
    pxiword size = pxmin(temp, self->length - self->size);

    if (size <= 0 || size > self->length) return 0;

    pxiword prev = self->head + self->length - size;

    self->size += size;
    self->head  = prev % self->length;

    pxiword index = 0;
    pxiword other = 0;

    while (index < size) {
        PxUtf8 utf8    = {0};
        pxi32  unicode = 0;

        other += pxUtf16ReadForw(memory, length, other, &unicode);

        pxUtf8Encode(&utf8, unicode);

        for (pxiword i = 0; i < utf8.size; i += 1) {
            pxiword j = self->head + index + i;

            self->memory[j % self->length] =
                utf8.items[i];
        }

        index += utf8.size;
    }

    return other;
}

pxiword
pxBuffer8WriteMemory32Head(PxBuffer8* self, pxu32* memory, pxiword length)
{
    pxiword temp = pxUtf8UnitsFromMemory32(memory, length);
    pxiword size = pxmin(temp, self->length - self->size);

    if (size <= 0 || size > self->length) return 0;

    pxiword prev = self->head + self->length - size;

    self->size += size;
    self->head  = prev % self->length;

    pxiword index = 0;
    pxiword other = 0;

    while (index < size) {
        PxUtf8 utf8    = {0};
        pxi32  unicode = 0;

        other += pxUtf32ReadForw(memory, length, other, &unicode);

        pxUtf8Encode(&utf8, unicode);

        for (pxiword i = 0; i < utf8.size; i += 1) {
            pxiword j = self->head + index + i;

            self->memory[j % self->length] =
                utf8.items[i];
        }

        index += utf8.size;
    }

    return other;
}

pxiword
pxBuffer8WriteString8Head(PxBuffer8* self, PxString8 string)
{
    return pxBuffer8WriteMemory8Head(self, string.memory, string.length);
}

pxiword
pxBuffer8WriteString16Head(PxBuffer8* self, PxString16 string)
{
    return pxBuffer8WriteMemory16Head(self, string.memory, string.length);
}

pxiword
pxBuffer8WriteString32Head(PxBuffer8* self, PxString32 string)
{
    return pxBuffer8WriteMemory32Head(self, string.memory, string.length);
}

pxiword
pxBuffer8WriteMemory16Tail(PxBuffer8* self, pxu16* memory, pxiword length)
{
    pxiword temp = pxUtf8UnitsFromMemory16(memory, length);
    pxiword size = pxmin(temp, self->length - self->size);

    if (size <= 0 || size > self->length) return 0;

    pxiword next = self->tail + size;

    pxiword index = 0;
    pxiword other = 0;

    while (index < size) {
        PxUtf8 utf8    = {0};
        pxi32  unicode = 0;

        other += pxUtf16ReadForw(memory, length, other, &unicode);

        pxUtf8Encode(&utf8, unicode);

        for (pxiword i = 0; i < utf8.size; i += 1) {
            pxiword j = self->tail + index + i;

            self->memory[j % self->length] =
                utf8.items[i];
        }

        index += utf8.size;
    }

    self->size += size;
    self->tail  = next % self->length;

    return other;
}

pxiword
pxBuffer8WriteMemory32Tail(PxBuffer8* self, pxu32* memory, pxiword length)
{
    pxiword temp = pxUtf8UnitsFromMemory32(memory, length);
    pxiword size = pxmin(temp, self->length - self->size);

    if (size <= 0 || size > self->length) return 0;

    pxiword next = self->tail + size;

    pxiword index = 0;
    pxiword other = 0;

    while (index < size) {
        PxUtf8 utf8    = {0};
        pxi32  unicode = 0;

        other += pxUtf32ReadForw(memory, length, other, &unicode);

        pxUtf8Encode(&utf8, unicode);

        for (pxiword i = 0; i < utf8.size; i += 1) {
            pxiword j = self->tail + index + i;

            self->memory[j % self->length] =
                utf8.items[i];
        }

        index += utf8.size;
    }

    self->size += size;
    self->tail  = next % self->length;

    return other;
}

pxiword
pxBuffer8WriteString8Tail(PxBuffer8* self, PxString8 string)
{
    return pxBuffer8WriteMemory8Tail(self, string.memory, string.length);
}

pxiword
pxBuffer8WriteString16Tail(PxBuffer8* self, PxString16 string)
{
    return pxBuffer8WriteMemory16Tail(self, string.memory, string.length);
}

pxiword
pxBuffer8WriteString32Tail(PxBuffer8* self, PxString32 string)
{
    return pxBuffer8WriteMemory32Tail(self, string.memory, string.length);
}

PxString8
pxBuffer8ReadString8Head(PxBuffer8* self, PxArena* arena, pxiword length)
{
    pxiword size = pxmin(self->size, length);

    if (size <= 0 || size > self->size) return (PxString8) {0};

    pxu8* result = pxArenaReserve(arena, pxu8, size + 1);

    if (result != 0) {
        pxBuffer8ReadMemory8Head(self,
            result, size);

        return pxString8Make(result, size);
    }

    return (PxString8) {0};
}

PxString8
pxBuffer8ReadString8Tail(PxBuffer8* self, PxArena* arena, pxiword length)
{
    pxiword size = pxmin(self->size, length);

    if (size <= 0 || size > self->size) return (PxString8) {0};

    pxu8* result = pxArenaReserve(arena, pxu8, size + 1);

    if (result != 0) {
        pxBuffer8ReadMemory8Tail(self,
            result, size);

        return pxString8Make(result, size);
    }

    return (PxString8) {0};
}

PxString8
pxBuffer8PeekString8Head(PxBuffer8* self, PxArena* arena, pxiword length)
{
    pxiword size = pxmin(self->size, length);

    if (size <= 0 || size > self->size) return (PxString8) {0};

    pxu8* result = pxArenaReserve(arena, pxu8, size + 1);

    if (result != 0) {
        pxBuffer8PeekMemory8Head(self,
            result, size);

        return pxString8Make(result, size);
    }

    return (PxString8) {0};
}

PxString8
pxBuffer8PeekString8Tail(PxBuffer8* self, PxArena* arena, pxiword length)
{
    pxiword size = pxmin(self->size, length);

    if (size <= 0 || size > self->size) return (PxString8) {0};

    pxu8* result = pxArenaReserve(arena, pxu8, size + 1);

    if (result != 0) {
        pxBuffer8PeekMemory8Tail(self,
            result, size);

        return pxString8Make(result, size);
    }

    return (PxString8) {0};
}

#endif // PX_CORE_STRING_BUFFERS_C
