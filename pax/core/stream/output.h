#ifndef PX_CORE_STREAM_OUTPUT_H
#define PX_CORE_STREAM_OUTPUT_H

#include "import.h"

typedef struct PxOutput
{
    void* ctxt;
    void* proc;
}
PxOutput;

typedef pxiword (PxOutputProc) (void*, pxu8*, pxiword);

PxOutput
pxOutputFromBuffer8(PxBuffer8* self);

pxiword
pxOutputMemory8(PxOutput self, pxu8* memory, pxiword length);

pxiword
pxOutputBuffer8(PxOutput self, PxBuffer8* value);

pxiword
pxOutputByte(PxOutput self, pxu8 value);

pxiword
pxOutputString8(PxOutput self, PxString8 value);

pxiword
pxOutputUnicode(PxOutput self, pxi32 value);

#endif // PX_CORE_STREAM_OUTPUT_H
