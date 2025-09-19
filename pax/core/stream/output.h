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
pxOutputNextMemory8(PxOutput self, pxu8* memory, pxiword length);

pxiword
pxOutputNextBuffer8(PxOutput self, PxBuffer8* value);

pxiword
pxOutputNextByte(PxOutput self, pxu8 value);

pxiword
pxOutputNextString8(PxOutput self, PxString8 value);

pxiword
pxOutputNextUnicode(PxOutput self, pxi32 value);

#endif // PX_CORE_STREAM_OUTPUT_H
