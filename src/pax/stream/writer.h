#ifndef PX_STREAM_WRITER_H
#define PX_STREAM_WRITER_H

#include "buffer8.h"

typedef pxint (PxWriterProc) (void*, PxBuffer8*);

typedef struct
{
    void* ctxt;
    void* proc;
}
PxWriter;

PxWriter
pxWriterFromBuffer8(PxBuffer8* buffer);

pxint
pxWriterFlush(PxWriter self, PxBuffer8* buffer);

pxint
pxWriterByte(PxWriter self, PxBuffer8* buffer, pxword8 value);

#endif // PX_STREAM_WRITER_H
