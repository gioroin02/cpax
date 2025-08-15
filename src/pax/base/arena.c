#ifndef PX_BASE_ARENA_C
#define PX_BASE_ARENA_C

#include "arena.h"

PxArena
pxArenaMake(pxn8* memory, pxint length)
{
    if (memory == 0 || length <= 0)
        return (PxArena) {0};

    return (PxArena) {
        .memory = memory,
        .length = length,
    };
}

void*
pxArenaReserve(PxArena* self, pxint amount, pxint stride)
{
    pxint length = amount * stride;

    if (amount <= 0 || stride <= 0) return 0;

    pxint start = pxArenaAlignForw(self, 16);
    pxint stop  = start + length;

    if (start < self->offset || stop > self->length)
        return 0;

    pxMemoryZero(self->memory + start, length, 1);

    self->offset = stop;

    return self->memory + start;
}

pxb8
pxArenaRelease(PxArena* self, void* value)
{
    return 0;
}

void
pxArenaClear(PxArena* self)
{
    self->offset = 0;
}

pxint
pxArenaOffset(PxArena* self)
{
    return self->offset;
}

pxb8
pxArenaRewind(PxArena* self, pxint offset)
{
    if (offset < 0 || offset >= self->length)
        return 0;

    self->offset = offset;

    return 1;
}

pxint
pxArenaAlignForw(PxArena* self, pxint align)
{
    if (align <= 0) return self->offset;

    pxint diff = self->offset % align;

    if (diff != 0)
        return self->offset + align - diff;

    return self->offset;
}

#endif // PX_BASE_ARENA_C
