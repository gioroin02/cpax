#ifndef PX_CORE_STREAM_TARGET_C
#define PX_CORE_STREAM_TARGET_C

#include "target.h"

PxTarget
pxTargetFromBuffer8(PxBuffer8* self)
{
    PxTarget result = {0};

    if (self == 0) return result;

    result.ctxt = self;
    result.proc = &pxBuffer8WriteMemory8Tail;

    return result;
}

pxiword
pxTargetMemory8(PxTarget self, pxu8* memory, pxiword length)
{
    PxTargetProc* proc = pxas(PxTargetProc*, self.proc);

    if (proc != 0)
        return proc(self.ctxt, memory, length);

    return 0;
}

pxiword
pxTargetBuffer8(PxTarget self, PxBuffer8* value)
{
    pxBuffer8Normalize(value);

    pxu8*   memory = value->memory;
    pxiword length = value->size;
    pxiword size   = 0;
    pxiword temp   = 0;

    for (;size < length; size += temp) {
        temp = pxTargetMemory8(self,
            memory + size, length - size);

        if (temp == 0) break;
    }

    value->size -= size;
    value->head  = (value->head + size) % value->length;

    return size;
}

pxiword
pxTargetByte(PxTarget self, pxu8 value)
{
    return pxTargetMemory8(self, &value, 1);
}

pxiword
pxTargetString8(PxTarget self, PxString8 value)
{
    pxu8*   memory = value.memory;
    pxiword length = value.length;
    pxiword size   = 0;
    pxiword temp   = 0;

    for (;size < length; size += temp) {
        temp = pxTargetMemory8(self,
            memory + size, length - size);

        if (temp == 0) break;
    }

    return size;
}

pxiword
pxTargetUnicode(PxTarget self, pxi32 value)
{
    pxiword result = 0;
    PxUtf8  utf8   = {0};

    if (pxUtf8Encode(&utf8, value) == 0) return result;

    result = pxTargetMemory8(self, utf8.items, utf8.size);

    return result;
}

#endif // PX_CORE_STREAM_TARGET_C
