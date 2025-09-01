#ifndef PX_STORAGE_PATH_C
#define PX_STORAGE_PATH_C

#include "path.h"

PxPath
pxPathFromString8(PxArena* arena, PxString8 string, PxString8 pivot)
{
    return (PxPath) {
        .items = pxStringListFromString8(arena, string, pivot),
    };
}

PxPath
pxPathFromString16(PxArena* arena, PxString16 string, PxString16 pivot)
{
    return (PxPath) {
        .items = pxStringListFromString16(arena, string, pivot),
    };
}

PxPath
pxPathFromString32(PxArena* arena, PxString32 string, PxString32 pivot)
{
    return (PxPath) {
        .items = pxStringListFromString32(arena, string, pivot),
    };
}

pxb8
pxPathInsertString8Head(PxPath* self, PxArena* arena, PxString8 value, PxString8 pivot)
{
    return pxStringListInsertString8Head(&self->items, arena, value, pivot);
}

pxb8
pxPathInsertString16Head(PxPath* self, PxArena* arena, PxString16 value, PxString16 pivot)
{
    return pxStringListInsertString16Head(&self->items, arena, value, pivot);
}

pxb8
pxPathInsertString32Head(PxPath* self, PxArena* arena, PxString32 value, PxString32 pivot)
{
    return pxStringListInsertString32Head(&self->items, arena, value, pivot);
}

pxb8
pxPathInsertString8Tail(PxPath* self, PxArena* arena, PxString8 value, PxString8 pivot)
{
    return pxStringListInsertString8Tail(&self->items, arena, value, pivot);
}

pxb8
pxPathInsertString16Tail(PxPath* self, PxArena* arena, PxString16 value, PxString16 pivot)
{
    return pxStringListInsertString16Tail(&self->items, arena, value, pivot);
}

pxb8
pxPathInsertString32Tail(PxPath* self, PxArena* arena, PxString32 value, PxString32 pivot)
{
    return pxStringListInsertString32Tail(&self->items, arena, value, pivot);
}

PxString8
pxString8FromPath(PxArena* arena, PxPath* value, PxString8 pivot)
{
    return pxString8FromStringList(arena, &value->items, pivot);
}

PxString16
pxString16FromPath(PxArena* arena, PxPath* value, PxString16 pivot)
{
    return pxString16FromStringList(arena, &value->items, pivot);
}

PxString32
pxString32FromPath(PxArena* arena, PxPath* value, PxString32 pivot)
{
    return pxString32FromStringList(arena, &value->items, pivot);
}

#endif // PX_STORAGE_PATH_C
