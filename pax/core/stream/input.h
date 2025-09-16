#ifndef PX_STREAM_INPUT_H
#define PX_STREAM_INPUT_H

#include "import.h"

typedef struct PxInput
{
    void* ctxt;
    void* proc;
}
PxInput;

typedef pxiword (PxInputProc) (void*, pxu8*, pxiword);

PxInput
pxInputFromBuffer(PxBuffer8* self);

pxiword
pxReadMemory8(PxInput* self, pxu8* memory, pxiword length);

pxiword
pxReadByte(PxInput* self, pxu8* value);

PxString8
pxReadString8(PxInput* self, PxArena* arena, pxiword length);

pxiword
pxReadBuffer8(PxInput* self, PxBuffer8* buffer);

#endif // PX_STREAM_INPUT_H
