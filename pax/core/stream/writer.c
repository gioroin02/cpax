#ifndef PX_CORE_STREAM_WRITER_C
#define PX_CORE_STREAM_WRITER_C

#include "writer.h"

PxWriter
pxWriterFromOutput(PxOutput output, PxArena* arena, pxiword length)
{
    PxWriter result = {0};

    result.buffer = pxBuffer8Reserve(arena, length);

    if (result.buffer.length > 0)
        result.output = output;

    return result;
}

pxiword
pxWriterFlush(PxWriter* self)
{
    return pxOutputNextBuffer8(self->output, &self->buffer);
}

pxiword
pxWriterNextMemory8(PxWriter* self, pxu8* memory, pxiword length)
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
pxWriterNextByte(PxWriter* self, pxu8 value)
{
    return pxWriterNextMemory8(self, &value, 1);
}

pxiword
pxWriterNextString8(PxWriter* self, PxString8 value)
{
    return pxWriterNextMemory8(self, value.memory, value.length);
}

pxiword
pxWriterNextUnicode(PxWriter* self, pxi32 value)
{
    PxUtf8 utf8 = {0};

    if (pxUtf8Encode(&utf8, value) == 0) return 0;

    pxu8*   memory = utf8.items;
    pxiword length = utf8.size;

    return pxWriterNextMemory8(self, memory, length);
}

#endif // PX_CORE_STREAM_WRITER_C
