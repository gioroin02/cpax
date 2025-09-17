#ifndef PX_STREAM_WRITER_C
#define PX_STREAM_WRITER_C

#include "writer.h"

PxWriter
pxWriterFromBuffer8(PxBuffer8* self)
{
    PxWriter result = {0};

    if (self == 0) return result;

    result.ctxt = self;
    result.proc = &pxBuffer8WriteMemory8Tail;

    return result;
}

pxiword
pxWriteMemory8(PxWriter self, pxu8* memory, pxiword length)
{
    PxWriterProc* proc = pxas(PxWriterProc*, self.proc);

    if (proc != 0)
        return proc(self.ctxt, memory, length);

    return 0;
}

pxiword
pxWriteByte(PxWriter self, pxu8 value)
{
    return pxWriteMemory8(self, &value, 1);
}

pxiword
pxWriteString8(PxWriter self, PxString8 value)
{
    pxu8*   memory = value.memory;
    pxiword length = value.length;
    pxiword size   = 0;
    pxiword temp   = 0;

    for (;size < length; size += temp) {
        temp = pxWriteMemory8(self,
            memory + size, length - size);

        if (temp == 0) break;
    }

    return size;
}

pxiword
pxWriteUnicode(PxWriter self, pxi32 value)
{
    pxiword result = 0;
    PxUtf8  utf8   = {0};

    if (pxUtf8Encode(&utf8, value) == 0) return result;

    result = pxWriteMemory8(self, utf8.items, utf8.size);

    return result;
}

pxiword
pxWriteBuffer8(PxWriter self, PxBuffer8* value)
{
    pxBuffer8Normalize(value);

    pxu8*   memory = value->memory;
    pxiword length = value->size;
    pxiword size   = 0;
    pxiword temp   = 0;

    for (;size < length; size += temp) {
        temp = pxWriteMemory8(self,
            memory + size, length - size);

        if (temp == 0) break;
    }

    value->size -= size;
    value->head  = (value->head + size) % value->length;

    return size;
}

#endif // PX_STREAM_WRITER_C
