#ifndef PX_STREAM_WRITER_H
#define PX_STREAM_WRITER_H

#include "import.h"

typedef struct PxWriter
{
    void* ctxt;
    void* proc;
}
PxWriter;

typedef pxiword (PxWriterProc) (void*, pxu8*, pxiword);

PxWriter
pxWriterFromBuffer8(PxBuffer8* self);

pxiword
pxWriteMemory8(PxWriter self, pxu8* memory, pxiword length);

pxiword
pxWriteByte(PxWriter self, pxu8 value);

pxiword
pxWriteString8(PxWriter self, PxString8 value);

pxiword
pxWriteUnicode(PxWriter self, pxi32 value);

pxiword
pxWriteBuffer8(PxWriter self, PxBuffer8* value);

#endif // PX_STREAM_WRITER_H
