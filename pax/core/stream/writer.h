#ifndef PX_CORE_STREAM_WRITER_H
#define PX_CORE_STREAM_WRITER_H

#include "target.h"

typedef struct PxWriter
{
    PxBuffer8 buffer;
    PxTarget  target;
}
PxWriter;

PxWriter
pxWriterFromTarget(PxTarget, PxArena* arena, pxiword length);

pxiword
pxWriterFlush(PxWriter* self);

pxiword
pxWriterMemory8(PxWriter* self, pxu8* memory, pxiword length);

pxiword
pxWriterMemory16(PxWriter* self, pxu16* memory, pxiword length);

pxiword
pxWriterMemory32(PxWriter* self, pxu32* memory, pxiword length);

pxiword
pxWriterByte(PxWriter* self, pxu8 value);

pxiword
pxWriterBuffer8(PxWriter* self, PxBuffer8* value);

pxiword
pxWriterBuffer16(PxWriter* self, PxBuffer16* value);

pxiword
pxWriterBuffer32(PxWriter* self, PxBuffer32* value);

pxiword
pxWriterString8(PxWriter* self, PxString8 value);

pxiword
pxWriterString16(PxWriter* self, PxString16 value);

pxiword
pxWriterString32(PxWriter* self, PxString32 value);

pxiword
pxWriterUnicode(PxWriter* self, pxi32 value);

#endif // PX_CORE_STREAM_WRITER_H
