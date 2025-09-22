#ifndef PX_CORE_STREAM_WRITER_C
#define PX_CORE_STREAM_WRITER_C

#include "writer.h"

PxWriter
pxWriterFromTarget(PxTarget target, PxArena* arena, pxiword length)
{
    PxWriter result = {0};

    result.buffer = pxBuffer8Reserve(arena, length);

    if (result.buffer.length > 0)
        result.target = target;

    return result;
}

pxiword
pxWriterFlush(PxWriter* self)
{
    return pxTargetBuffer8(self->target, &self->buffer);
}

pxiword
pxWriterMemory8(PxWriter* self, pxu8* memory, pxiword length)
{
    pxiword temp = 0;

    for (pxiword i = 0; i < length; i += temp) {
        if (length - i > 0) pxWriterFlush(self);

        temp = pxBuffer8WriteMemory8Tail(
            &self->buffer, memory + i, length - i);

        if (temp == 0) return i;
    }

    return length;
}

pxiword
pxWriterMemory16(PxWriter* self, pxu16* memory, pxiword length)
{
    pxiword result = 0;

    for (pxiword i = 0; i < length;) {
        pxi32 unicode = 0;

        if (length - i > 0) pxWriterFlush(self);

        i += pxUtf16ReadForw(memory, length, i, &unicode);

        result += pxBuffer8WriteUnicodeTail(
            &self->buffer, unicode);
    }

    return result;
}

pxiword
pxWriterMemory32(PxWriter* self, pxu32* memory, pxiword length)
{
    pxiword result = 0;

    for (pxiword i = 0; i < length;) {
        pxi32 unicode = 0;

        if (length - i > 0) pxWriterFlush(self);

        i += pxUtf32ReadForw(memory, length, i, &unicode);

        result += pxBuffer8WriteUnicodeTail(
            &self->buffer, unicode);
    }

    return result;
}

pxiword
pxWriterByte(PxWriter* self, pxu8 value)
{
    return pxWriterMemory8(self, &value, 1);
}

pxiword
pxWriterBuffer8(PxWriter* self, PxBuffer8* value)
{
    pxBuffer8Normalize(value);

    pxu8*   memory = value->memory;
    pxiword length = value->size;

    pxiword size = pxWriterMemory8(self, memory, length);

    value->size -= size;
    value->head  = (value->head + size) % value->length;

    return size;
}

pxiword
pxWriterBuffer16(PxWriter* self, PxBuffer16* value)
{
    pxBuffer16Normalize(value);

    pxu16*  memory = value->memory;
    pxiword length = value->size;

    pxiword size = pxWriterMemory16(self, memory, length);

    value->size -= size;
    value->head  = (value->head + size) % value->length;

    return size;
}

pxiword
pxWriterBuffer32(PxWriter* self, PxBuffer32* value)
{
    pxBuffer32Normalize(value);

    pxu32*  memory = value->memory;
    pxiword length = value->size;

    pxiword size = pxWriterMemory32(self, memory, length);

    value->size -= size;
    value->head  = (value->head + size) % value->length;

    return size;
}

pxiword
pxWriterString8(PxWriter* self, PxString8 value)
{
    return pxWriterMemory8(self, value.memory, value.length);
}

pxiword
pxWriterString16(PxWriter* self, PxString16 value)
{
    return pxWriterMemory16(self, value.memory, value.length);
}

pxiword
pxWriterString32(PxWriter* self, PxString32 value)
{
    return pxWriterMemory32(self, value.memory, value.length);
}

pxiword
pxWriterUnicode(PxWriter* self, pxi32 value)
{
    PxUtf8 utf8 = {0};

    if (pxUtf8Encode(&utf8, value) == 0) return 0;

    pxu8*   memory = utf8.items;
    pxiword length = utf8.size;

    return pxWriterMemory8(self, memory, length);
}

#endif // PX_CORE_STREAM_WRITER_C
