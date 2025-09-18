#ifndef PX_CORE_STREAM_INPUT_H
#define PX_CORE_STREAM_INPUT_H

#include "import.h"

typedef struct PxInput
{
    void* ctxt;
    void* proc;
}
PxInput;

typedef pxiword (PxInputProc) (void*, pxu8*, pxiword);

PxInput
pxInputFromBuffer8(PxBuffer8* self);

pxiword
pxInputMemory8(PxInput self, pxu8* memory, pxiword length);

pxiword
pxInputBuffer8(PxInput self, PxBuffer8* buffer);

pxiword
pxInputByte(PxInput self, pxu8* value);

#endif // PX_CORE_STREAM_INPUT_H
