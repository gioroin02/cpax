#ifndef PX_STREAM_READER_H
#define PX_STREAM_READER_H

#include "import.h"

typedef struct PxReader
{
    void* ctxt;
    void* proc;
}
PxReader;

typedef pxiword (PxReaderProc) (void*, pxu8*, pxiword);

PxReader
pxReaderFromBuffer8(PxBuffer8* self);

pxiword
pxReadMemory8(PxReader self, pxu8* memory, pxiword length);

pxiword
pxReadByte(PxReader self, pxu8* value);

PxString8
pxReadString8(PxReader self, PxArena* arena, pxiword length);

pxiword
pxReadBuffer8(PxReader self, PxBuffer8* buffer);

#endif // PX_STREAM_READER_H
