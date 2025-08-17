#ifndef PX_MEMORY_SYSTEM_H
#define PX_MEMORY_SYSTEM_H

#include "import.h"

pxint
pxMemoryPageSize();

PxArena
pxMemoryReserve(pxint amount);

void
pxMemoryRelease(PxArena* arena);

#endif // PX_MEMORY_SYSTEM_H
