#ifndef PX_STREAM_INPUT_C
#define PX_STREAM_INPUT_C

#include "input.h"

PxInput
pxInputFromBuffer(PxBuffer8* self)
{
    PxInput result = {0};

    if (self == 0) return result;

    result.ctxt = self;
    result.proc = &pxBuffer8ReadMemory8Head;

    return result;
}

pxiword
pxReadMemory8(PxInput* self, pxu8* memory, pxiword length)
{
    PxInputProc* proc = pxas(PxInputProc*, self->proc);

    if (proc != 0)
        return proc(self->ctxt, memory, length);

    return 0;
}

pxiword
pxReadByte(PxInput* self, pxu8* value)
{
    pxu8 temp = 0;

    pxiword result =
        pxReadMemory8(self, &temp, 1);

    if (value != 0) *value = temp;

    return result;
}

PxString8
pxReadString8(PxInput* self, PxArena* arena, pxiword length)
{
    pxiword offset = pxArenaOffset(arena);

    if (length <= 0) return (PxString8) {0};

    pxu8* result =
        pxArenaReserve(arena, pxu8, length + 1);

    pxiword size = pxReadMemory8(self, result, length);

    pxArenaRewind(arena, offset + size + 1);

    return pxString8Make(result, size);
}

pxiword
pxReadBuffer8(PxInput* self, PxBuffer8* buffer)
{
    pxBuffer8Normalize(buffer);

    pxu8*   memory = buffer->memory + buffer->size;
    pxiword length = buffer->length - buffer->size;

    pxiword size = pxReadMemory8(self, memory, length);

    buffer->size += size;
    buffer->tail  = (buffer->tail + size) % buffer->length;

    return size;
}

#endif // PX_STREAM_INPUT_C
