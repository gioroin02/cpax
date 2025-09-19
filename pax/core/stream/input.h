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
pxInputNextMemory8(PxInput self, pxu8* memory, pxiword length);

pxiword
pxInputNextBuffer8(PxInput self, PxBuffer8* buffer);

pxiword
pxInputNextByte(PxInput self, pxu8* value);

PxString8
pxInputNextString8(PxInput self, PxArena* arena, pxiword length);

#endif // PX_CORE_STREAM_INPUT_H
