#ifndef PX_STREAM_WRITER_C
#define PX_STREAM_WRITER_C

#include "writer.h"

PxWriter
pxBufferWriter(PxBuffer8* self, PxBuffer8* buffer)
{
    if (self == 0 || buffer == 0)
        return (PxWriter) {0};

    return (PxWriter) {
        .buffer = buffer,
        .ctxt   = self,
        .proc   = &pxBuffer8WriteTail,
    };
}

PxBuffer8*
pxWriterSetBuffer(PxWriter* self, PxBuffer8* buffer)
{
    PxBuffer8* result = self->buffer;

    if (buffer != 0)
        self->buffer = buffer;
    else
        return 0;

    return result;
}

pxiword
pxWriterFlush(PxWriter* self)
{
    PxWriterProc* proc = pxCast(PxWriterProc*, self->proc);

    if (proc != 0)
        return proc(self->ctxt, self->buffer);

    return 0;
}

pxiword
pxWriterByte(PxWriter* self, pxu8 value)
{
    if (self->buffer->size + 1 > self->buffer->length)
        pxWriterFlush(self);

    return pxBuffer8WriteMemory8Tail(self->buffer, &value, 1);
}

pxiword
pxWriterString8(PxWriter* self, PxString8 value)
{
    for (pxiword i = 0; i < value.length;) {
        i += pxBuffer8WriteMemory8Tail(self->buffer,
            value.memory + i, value.length - i);

        pxWriterFlush(self);
    }

    return value.length;
}

pxiword
pxWriterString16(PxWriter* self, PxString16 value)
{
    for (pxiword i = 0; i < value.length;) {
        i += pxBuffer8WriteMemory16Tail(self->buffer,
            value.memory + i, value.length - i);

        pxWriterFlush(self);
    }

    return value.length;
}

pxiword
pxWriterString32(PxWriter* self, PxString32 value)
{
    for (pxiword i = 0; i < value.length;) {
        i += pxBuffer8WriteMemory32Tail(self->buffer,
            value.memory + i, value.length - i);

        pxWriterFlush(self);
    }

    return value.length;
}

pxiword
pxWriterBuffer8(PxWriter* self, PxBuffer8* value)
{
    pxiword length = value->size;

    for (pxiword i = 0; i < length;) {
        i += pxBuffer8WriteTail(self->buffer,
            value);

        pxWriterFlush(self);
    }

    return length;
}

pxiword
pxWriterMemory(PxWriter* self, void* memory, pxiword amount, pxiword stride)
{
    pxiword length = amount * stride;

    for (pxiword i = 0; i < length;) {
        i += pxBuffer8WriteMemory8Tail(self->buffer,
            pxCast(pxu8*, memory) + i, length - i);

        pxWriterFlush(self);
    }

    return length;
}

#endif // PX_STREAM_WRITER_C
