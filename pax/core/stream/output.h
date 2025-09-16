#ifndef PX_STREAM_OUTPUT_H
#define PX_STREAM_OUTPUT_H

#include "import.h"

typedef struct PxOutput
{
    void* ctxt;
    void* proc;
}
PxOutput;

typedef pxiword (PxOutputProc) (void*, pxu8*, pxiword);

PxOutput
pxBufferOutput(PxBuffer8* self);

pxiword
pxWriteMemory8(PxOutput* self, pxu8* memory, pxiword length);

pxiword
pxWriteByte(PxOutput* self, pxu8 value);

pxiword
pxWriteString8(PxOutput* self, PxString8 value);

pxiword
pxWriteUnicode(PxOutput* self, pxi32 value);

pxiword
pxWriteBuffer8(PxOutput* self, PxBuffer8* value);

#endif // PX_STREAM_OUTPUT_H
