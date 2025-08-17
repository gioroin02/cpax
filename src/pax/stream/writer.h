#ifndef PX_STREAM_WRITER_H
#define PX_STREAM_WRITER_H

#include "buffer8.h"

typedef pxint (PxWriterProc) (void*, PxBuffer8*);

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

pxint
pxWriterFlush(PxWriter* self);

pxint
pxWriterByte(PxWriter* self, pxword8 value);

pxint
pxWriterString(PxWriter* self, PxString8 value);

#endif // PX_STREAM_WRITER_H
