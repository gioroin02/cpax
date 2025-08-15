#ifndef PX_STREAM_READER_H
#define PX_STREAM_READER_H

#include "buf8.h"

typedef pxint (PxReaderProc) (void*, PxBuffer8*);

typedef struct
{
    void* ctxt;
    void* proc;
}
PxReader;

PxReader
pxReaderFromBuffer8(PxBuffer8* buffer);

pxint
pxReaderFill(PxReader self, PxBuffer8* buffer);

pxn8
pxReaderPeek(PxReader self, PxBuffer8* buffer, pxint offset);

pxn8
pxReaderMove(PxReader self, PxBuffer8* buffer, pxint offset);

#endif // PX_STREAM_READER_H
