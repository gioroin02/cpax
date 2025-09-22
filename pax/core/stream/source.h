#ifndef PX_CORE_STREAM_SOURCE_H
#define PX_CORE_STREAM_SOURCE_H

#include "import.h"

typedef struct PxSource
{
    void* ctxt;
    void* proc;
}
PxSource;

typedef pxiword (PxSourceProc) (void*, pxu8*, pxiword);

PxSource
pxSourceFromBuffer8(PxBuffer8* self);

pxiword
pxSourceMemory8(PxSource self, pxu8* memory, pxiword length);

pxiword
pxSourceBuffer8(PxSource self, PxBuffer8* buffer);

pxiword
pxSourceByte(PxSource self, pxu8* value);

PxString8
pxSourceString8(PxSource self, PxArena* arena, pxiword length);

#endif // PX_CORE_STREAM_SOURCE_H
