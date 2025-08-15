#ifndef PX_STREAM_WRITER_C
#define PX_STREAM_WRITER_C

#include "writer.h"

PxWriter
pxWriterFromBuffer8(PxBuffer8* buffer)
{
    if (buffer == 0)
        return (PxWriter) {0};

    return (PxWriter) {
        .ctxt = buffer,
        .proc = &pxBuffer8WriteTail,
    };
}

pxint
pxWriterFlush(PxWriter self, PxBuffer8* buffer)
{
    PxWriterProc* proc = px_as(PxWriterProc*, self.proc);

    if (proc != 0)
        return proc(self.ctxt, buffer);

    return 0;
}

pxint
pxWriterByte(PxWriter self, PxBuffer8* buffer, pxn8 value)
{
    if (buffer->size + 1 > buffer->length)
        pxWriterFlush(self, buffer);

    return pxBuffer8WriteMemory8Tail(buffer, &value, 1);
}

#endif // PX_STREAM_WRITER_C
