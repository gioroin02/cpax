#ifndef PX_BASE_ARENA_H
#define PX_BASE_ARENA_H

#include "memory.h"

#define pxArenaReserveOneOf(arena, type) \
    pxCast(type*, pxArenaReserve(arena, 1, pxSize(type)))

#define pxArenaReserveManyOf(arena, type, amount) \
    pxCast(type*, pxArenaReserve(arena, amount, pxSize(type)))

typedef struct
{
    pxword8* memory;
    pxint    length;
    pxint    offset;
}
PxArena;

PxArena
pxArenaMake(pxword8* memory, pxint length);

void*
pxArenaReserve(PxArena* self, pxint amount, pxint stride);

pxbool8
pxArenaRelease(PxArena* self, void* value);

void
pxArenaClear(PxArena* self);

pxint
pxArenaOffset(PxArena* self);

pxbool8
pxArenaRewind(PxArena* self, pxint offset);

pxint
pxArenaAlignForw(PxArena* self, pxint align);

#endif // PX_BASE_ARENA_H
