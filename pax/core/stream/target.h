#ifndef PX_CORE_STREAM_TARGET_H
#define PX_CORE_STREAM_TARGET_H

#include "import.h"

typedef struct PxTarget
{
    void* ctxt;
    void* proc;
}
PxTarget;

typedef pxiword (PxTargetProc) (void*, pxu8*, pxiword);

PxTarget
pxTargetFromBuffer8(PxBuffer8* self);

pxiword
pxTargetMemory8(PxTarget self, pxu8* memory, pxiword length);

pxiword
pxTargetBuffer8(PxTarget self, PxBuffer8* value);

pxiword
pxTargetByte(PxTarget self, pxu8 value);

pxiword
pxTargetString8(PxTarget self, PxString8 value);

pxiword
pxTargetUnicode(PxTarget self, pxi32 value);

#endif // PX_CORE_STREAM_TARGET_H
