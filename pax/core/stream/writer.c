#ifndef PX_STREAM_WRITER_C
#define PX_STREAM_WRITER_C

#include "writer.h"

PxWriter
pxBufferWriter(PxBuffer8* self, PxArena* arena, pxiword length)
{
    PxWriter result = {0};

    if (self == 0 || length <= 0) return result;

    result.buffer = pxBuffer8Reserve(arena, length);

    if (result.buffer.length > 0) {
        result.ctxt = self;
        result.proc = &pxBuffer8WriteTail;
    }

    return result;
}

pxiword
pxWriterFlush(PxWriter* self)
{
    PxWriterProc* proc = pxas(PxWriterProc*, self->proc);

    if (proc != 0)
        return proc(self->ctxt, &self->buffer);

    return 0;
}

pxiword
pxWriterByte(PxWriter* self, pxu8 value)
{
    if (self->buffer.size + 1 > self->buffer.length)
        pxWriterFlush(self);

    return pxBuffer8WriteMemory8Tail(&self->buffer, &value, 1);
}

pxiword
pxWriterMemory(PxWriter* self, void* memory, pxiword amount, pxiword stride)
{
    pxiword length = amount * stride;
    pxiword temp   = 0;

    for (pxiword i = 0; i < length; i += temp) {
        temp = pxBuffer8WriteMemory8Tail(&self->buffer,
            pxas(pxu8*, memory) + i, length - i);

        if (temp == 0) pxWriterFlush(self);
    }

    return length;
}

pxiword
pxWriterUnicode(PxWriter* self, PxArena* arena, pxi32 value)
{
    pxiword offset = pxArenaOffset(arena);

    PxString8 string =
        pxString8CopyUnicode(arena, value);

    pxiword result = pxWriterString8(self, string);

    pxArenaRewind(arena, offset);

    return result;
}

pxiword
pxWriterString8(PxWriter* self, PxString8 value)
{
    pxiword temp = 0;

    for (pxiword i = 0; i < value.length; i += temp) {
        temp = pxBuffer8WriteMemory8Tail(&self->buffer,
            value.memory + i, value.length - i);

        if (temp == 0) pxWriterFlush(self);
    }

    return value.length;
}

pxiword
pxWriterString16(PxWriter* self, PxString16 value)
{
    pxiword temp = 0;

    for (pxiword i = 0; i < value.length; i += temp) {
        temp = pxBuffer8WriteMemory16Tail(&self->buffer,
            value.memory + i, value.length - i);

        if (temp == 0) pxWriterFlush(self);
    }

    return value.length;
}

pxiword
pxWriterString32(PxWriter* self, PxString32 value)
{
    pxiword temp = 0;

    for (pxiword i = 0; i < value.length; i += temp) {
        temp = pxBuffer8WriteMemory32Tail(&self->buffer,
            value.memory + i, value.length - i);

        if (temp == 0) pxWriterFlush(self);
    }

    return value.length;
}

pxiword
pxWriterBuffer8(PxWriter* self, PxBuffer8* value)
{
    pxiword length = value->size;
    pxiword temp   = 0;

    for (pxiword i = 0; i < length; i += temp) {
        temp = pxBuffer8WriteTail(
            &self->buffer, value);

        if (temp == 0) pxWriterFlush(self);
    }

    return length;
}

pxiword
pxWriterBuffer16(PxWriter* self, PxBuffer16* value)
{
    pxiword length = value->size;
    pxiword temp   = 0;

    pxBuffer16Normalize(value);

    for (pxiword i = 0; i < length; i += temp) {
        temp = pxBuffer8WriteMemory16Tail(&self->buffer,
            value->memory + value->head, value->size);

        value->size -= temp;
        value->head  = (value->head + temp) % value->length;

        if (temp == 0) pxWriterFlush(self);
    }

    return length;
}

pxiword
pxWriterBuffer32(PxWriter* self, PxBuffer32* value)
{
    pxiword length = value->size;
    pxiword temp   = 0;

    pxBuffer32Normalize(value);

    for (pxiword i = 0; i < length; i += temp) {
        temp = pxBuffer8WriteMemory32Tail(&self->buffer,
            value->memory + value->head, value->size);

        value->size -= temp;
        value->head  = (value->head + temp) % value->length;

        if (temp == 0) pxWriterFlush(self);
    }

    return length;
}

#endif // PX_STREAM_WRITER_C
