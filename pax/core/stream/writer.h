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
pxWriterNextMemory8(PxWriter* self, pxu8* memory, pxiword length);

pxiword
pxWriterNextMemory16(PxWriter* self, pxu16* memory, pxiword length);

pxiword
pxWriterNextMemory32(PxWriter* self, pxu32* memory, pxiword length);

pxiword
pxWriterNextByte(PxWriter* self, pxu8 value);

pxiword
pxWriterNextString8(PxWriter* self, PxString8 value);

pxiword
pxWriterNextString16(PxWriter* self, PxString16 value);

pxiword
pxWriterNextString32(PxWriter* self, PxString32 value);

pxiword
pxWriterNextUnicode(PxWriter* self, pxi32 value);

#endif // PX_CORE_STREAM_WRITER_H
