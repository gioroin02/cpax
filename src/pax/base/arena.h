#ifndef PX_BASE_ARENA_H
#define PX_BASE_ARENA_H

#include "memory.h"

#define pxArenaReserve(arena, type, amount) \
    pxCast(type*, pxArenaReserveMemory(arena, amount, pxSize(type)))

typedef struct PxArena
{
    pxword8* memory;
    pxint    length;
    pxint    offset;
}
PxArena;

PxArena
pxArenaMake(pxword8* memory, pxint length);

void*
pxArenaReserveMemory(PxArena* self, pxint amount, pxint stride);

pxbool8
pxArenaReleaseMemory(PxArena* self, void* memory);

void*
pxArenaCopyMemory(PxArena* self, void* memory, pxint amount, pxint stride);

void
pxArenaClear(PxArena* self);

pxint
pxArenaOffset(PxArena* self);

pxbool8
pxArenaRewind(PxArena* self, pxint offset);

pxint
pxArenaAlignForw(PxArena* self, pxint align);

#endif // PX_BASE_ARENA_H
