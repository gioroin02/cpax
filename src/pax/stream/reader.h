#ifndef PX_STREAM_READER_H
#define PX_STREAM_READER_H

#include "buffer8.h"

typedef pxint (PxReaderProc) (void*, PxBuffer8*);

typedef struct
{
    PxBuffer8* buffer;

    void* ctxt;
    void* proc;
}
PxReader;

PxReader
pxReaderFromBuffer(PxBuffer8* source, PxBuffer8* buffer);

PxBuffer8*
pxReaderSetBuffer(PxReader* self, PxBuffer8* buffer);

pxint
pxReaderFill(PxReader* self);

pxword8
pxReaderDrop(PxReader* self, pxint offset);

pxword8
pxReaderPeek(PxReader* self, pxint offset);

PxString8
pxReaderPeekString(PxReader* self, PxArena* arena, pxint length);

PxString8
pxReaderPeekLine(PxReader* self, PxArena* arena, pxint length);

PxString8
pxReaderString(PxReader* self, PxArena* arena, pxint length);

PxString8
pxReaderLine(PxReader* self, PxArena* arena, pxint length);

#endif // PX_STREAM_READER_H
