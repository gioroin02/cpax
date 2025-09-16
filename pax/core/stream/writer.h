#ifndef PX_STREAM_WRITER_H
#define PX_STREAM_WRITER_H

#include "import.h"

typedef pxiword (PxWriterProc) (void*, PxBuffer8*);

typedef struct PxWriter
{
    PxBuffer8 buffer;

    void* ctxt;
    void* proc;
}
PxWriter;

PxWriter
pxBufferWriter(PxBuffer8* self, PxArena* arena, pxiword length);

pxiword
pxWriterFlush(PxWriter* self);

pxiword
pxWriterByte(PxWriter* self, pxu8 value);

pxiword
pxWriterMemory(PxWriter* self, void* memory, pxiword amount, pxiword stride);

pxiword
pxWriterUnicode(PxWriter* self, PxArena* arena, pxi32 value);

pxiword
pxWriterString8(PxWriter* self, PxString8 value);

pxiword
pxWriterString16(PxWriter* self, PxString16 value);

pxiword
pxWriterString32(PxWriter* self, PxString32 value);

pxiword
pxWriterBuffer8(PxWriter* self, PxBuffer8* value);

pxiword
pxWriterBuffer16(PxWriter* self, PxBuffer16* value);

pxiword
pxWriterBuffer32(PxWriter* self, PxBuffer32* value);

/*
pxiword
pxWriterFormatList(PxWriter* self, pxiword start, pxiword stop, PxFormatCmd* list);

pxiword
pxWriterFormat(PxWriter* self, PxString8 format, pxiword start, pxiword stop, PxFormatCmd* list);
*/

#endif // PX_STREAM_WRITER_H
