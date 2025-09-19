#ifndef PX_CORE_STREAM_INPUT_C
#define PX_CORE_STREAM_INPUT_C

#include "input.h"

PxInput
pxInputFromBuffer8(PxBuffer8* self)
{
    PxInput result = {0};

    if (self == 0) return result;

    result.ctxt = self;
    result.proc = &pxBuffer8ReadMemory8Head;

    return result;
}

pxiword
pxInputNextMemory8(PxInput self, pxu8* memory, pxiword length)
{
    PxInputProc* proc = pxas(PxInputProc*, self.proc);

    if (proc != 0)
        return proc(self.ctxt, memory, length);

    return 0;
}

pxiword
pxInputNextBuffer8(PxInput self, PxBuffer8* buffer)
{
    pxBuffer8Normalize(buffer);

    pxu8*   memory = buffer->memory + buffer->size;
    pxiword length = buffer->length - buffer->size;

    pxiword size = pxInputNextMemory8(self, memory, length);

    buffer->size += size;
    buffer->tail  = (buffer->tail + size) % buffer->length;

    return size;
}

pxiword
pxInputNextByte(PxInput self, pxu8* value)
{
    pxu8 temp = 0;

    pxiword result = pxInputNextMemory8(self, &temp, 1);

    if (value != 0) *value = temp;

    return result;
}

PxString8
pxInputNextString8(PxInput self, PxArena* arena, pxiword length)
{
    pxiword offset = pxArenaOffset(arena);
    pxu8*   memory = pxArenaReserve(arena, pxu8, length + 1);

    pxiword size =
        pxInputNextMemory8(self, memory, length);

    if (size < length)
        pxArenaRewind(arena, offset + size + 1);

    return pxString8Make(memory, size);
}

#endif // PX_CORE_STREAM_INPUT_C
