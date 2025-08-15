#ifndef PX_BASE_ARENA_H
#define PX_BASE_ARENA_H

#include "memory.h"

#define pxArenaReserveOne(arena, type, amount) \
    pxArenaReserve(arena, amount, px_size(type))

typedef struct
{
    pxn8* memory;
    pxint length;
    pxint offset;
}
PxArena;

PxArena
pxArenaMake(pxn8* memory, pxint length);

void*
pxArenaReserve(PxArena* self, pxint amount, pxint stride);

pxb8
pxArenaRelease(PxArena* self, void* value);

void
pxArenaClear(PxArena* self);

pxint
pxArenaOffset(PxArena* self);

pxb8
pxArenaRewind(PxArena* self, pxint offset);

pxint
pxArenaAlignForw(PxArena* self, pxint align);

#endif // PX_BASE_ARENA_H
