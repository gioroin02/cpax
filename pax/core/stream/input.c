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
pxInputMemory8(PxInput self, pxu8* memory, pxiword length)
{
    PxInputProc* proc = pxas(PxInputProc*, self.proc);

    if (proc != 0)
        return proc(self.ctxt, memory, length);

    return 0;
}

pxiword
pxInputBuffer8(PxInput self, PxBuffer8* buffer)
{
    pxBuffer8Normalize(buffer);

    pxu8*   memory = buffer->memory + buffer->size;
    pxiword length = buffer->length - buffer->size;

    pxiword size = pxInputMemory8(self, memory, length);

    buffer->size += size;
    buffer->tail  = (buffer->tail + size) % buffer->length;

    return size;
}

pxiword
pxInputByte(PxInput self, pxu8* value)
{
    pxu8 temp = 0;

    pxiword result = pxInputMemory8(self, &temp, 1);

    if (value != 0) *value = temp;

    return result;
}

#endif // PX_CORE_STREAM_INPUT_C
