#ifndef PX_CORE_STREAM_WRITER_H
#define PX_CORE_STREAM_WRITER_H

#include "output.h"

typedef struct PxWriter
{
    PxBuffer8 buffer;
    PxOutput  output;
}
PxWriter;

PxWriter
pxWriterFromOutput(PxOutput, PxArena* arena, pxiword length);

pxiword
pxWriterFlush(PxWriter* self);

pxiword
pxWriterMemory8(PxWriter* self, pxu8* memory, pxiword length);

pxiword
pxWriterByte(PxWriter* self, pxu8 value);

pxiword
pxWriterString8(PxWriter* self, PxString8 value);

pxiword
pxWriterUnicode(PxWriter* self, pxi32 value);

#endif // PX_CORE_STREAM_WRITER_H
