#ifndef PX_CORE_STREAM_SOURCE_C
#define PX_CORE_STREAM_SOURCE_C

#include "source.h"

PxSource
pxSourceFromBuffer8(PxBuffer8* self)
{
    PxSource result = {0};

    if (self == 0) return result;

    result.ctxt = self;
    result.proc = &pxBuffer8ReadMemory8Head;

    return result;
}

pxiword
pxSourceMemory8(PxSource self, pxu8* memory, pxiword length)
{
    PxSourceProc* proc = pxas(PxSourceProc*, self.proc);

    if (proc != 0)
        return proc(self.ctxt, memory, length);

    return 0;
}

pxiword
pxSourceBuffer8(PxSource self, PxBuffer8* buffer)
{
    pxBuffer8Normalize(buffer);

    pxu8*   memory = buffer->memory + buffer->size;
    pxiword length = buffer->length - buffer->size;

    pxiword size = pxSourceMemory8(self, memory, length);

    buffer->size += size;
    buffer->tail  = (buffer->tail + size) % buffer->length;

    return size;
}

pxiword
pxSourceByte(PxSource self, pxu8* value)
{
    pxu8 temp = 0;

    pxiword result = pxSourceMemory8(self, &temp, 1);

    if (value != 0) *value = temp;

    return result;
}

PxString8
pxSourceString8(PxSource self, PxArena* arena, pxiword length)
{
    pxiword offset = pxArenaOffset(arena);
    pxu8*   memory = pxArenaReserve(arena, pxu8, length + 1);

    pxiword size =
        pxSourceMemory8(self, memory, length);

    if (size < length)
        pxArenaRewind(arena, offset + size + 1);

    return pxString8Make(memory, size);
}

#endif // PX_CORE_STREAM_SOURCE_C
