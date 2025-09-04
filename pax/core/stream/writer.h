#ifndef PX_STREAM_WRITER_H
#define PX_STREAM_WRITER_H

#include "buffer8.h"

typedef pxiword (PxWriterProc) (void*, PxBuffer8*);

typedef struct PxWriter
{
    PxBuffer8* buffer;

    void* ctxt;
    void* proc;
}
PxWriter;

PxWriter
pxBufferWriter(PxBuffer8* self, PxBuffer8* buffer);

PxBuffer8*
pxWriterSetBuffer(PxWriter* self, PxBuffer8* buffer);

pxiword
pxWriterFlush(PxWriter* self);

pxiword
pxWriterByte(PxWriter* self, pxu8 value);

pxiword
pxWriterString8(PxWriter* self, PxString8 value);

pxiword
pxWriterBuffer8(PxWriter* self, PxBuffer8* value);

pxiword
pxWriterMemory(PxWriter* self, void* memory, pxiword amount, pxiword stride);

#endif // PX_STREAM_WRITER_H
