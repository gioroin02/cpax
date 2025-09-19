#ifndef PX_CORE_STREAM_OUTPUT_C
#define PX_CORE_STREAM_OUTPUT_C

#include "output.h"

PxOutput
pxOutputFromBuffer8(PxBuffer8* self)
{
    PxOutput result = {0};

    if (self == 0) return result;

    result.ctxt = self;
    result.proc = &pxBuffer8WriteMemory8Tail;

    return result;
}

pxiword
pxOutputNextMemory8(PxOutput self, pxu8* memory, pxiword length)
{
    PxOutputProc* proc = pxas(PxOutputProc*, self.proc);

    if (proc != 0)
        return proc(self.ctxt, memory, length);

    return 0;
}

pxiword
pxOutputNextBuffer8(PxOutput self, PxBuffer8* value)
{
    pxBuffer8Normalize(value);

    pxu8*   memory = value->memory;
    pxiword length = value->size;
    pxiword size   = 0;
    pxiword temp   = 0;

    for (;size < length; size += temp) {
        temp = pxOutputNextMemory8(self,
            memory + size, length - size);

        if (temp == 0) break;
    }

    value->size -= size;
    value->head  = (value->head + size) % value->length;

    return size;
}

pxiword
pxOutputNextByte(PxOutput self, pxu8 value)
{
    return pxOutputNextMemory8(self, &value, 1);
}

pxiword
pxOutputNextString8(PxOutput self, PxString8 value)
{
    pxu8*   memory = value.memory;
    pxiword length = value.length;
    pxiword size   = 0;
    pxiword temp   = 0;

    for (;size < length; size += temp) {
        temp = pxOutputNextMemory8(self,
            memory + size, length - size);

        if (temp == 0) break;
    }

    return size;
}

pxiword
pxOutputNextUnicode(PxOutput self, pxi32 value)
{
    pxiword result = 0;
    PxUtf8  utf8   = {0};

    if (pxUtf8Encode(&utf8, value) == 0) return result;

    result = pxOutputNextMemory8(self, utf8.items, utf8.size);

    return result;
}

#endif // PX_CORE_STREAM_OUTPUT_C
