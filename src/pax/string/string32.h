#ifndef PX_STRING_STRING32_H
#define PX_STRING_STRING32_H

#include "utf32.h"

typedef struct PxString32
{
    pxword32* memory;
    pxint     length;
}
PxString32;

PxString32
pxString32FromUnicode(PxArena* arena, pxint32 value);

PxString32
pxString32Copy(PxArena* arena, PxString32 string);

PxString32
pxString32CopyMemory(PxArena* arena, pxword32* memory, pxint length);

PxString32
pxString32Chain(PxString32 self, PxArena* arena, PxString32 value);

PxString32
pxString32ChainMemory(PxString32 self, PxArena* arena, pxword32* memory, pxint length);

pxbool32
pxString32Get(PxString32 self, pxint index, pxword32* value);

pxword32
pxString32GetOr(PxString32 self, pxint index, pxword32 value);

pxbool32
pxString32IsEqual(PxString32 self, PxString32 value);

pxbool32
pxString32IsEqualMemory(PxString32 self, pxword32* memory, pxint length);

pxbool32
pxString32BeginsWith(PxString32 self, PxString32 value);

pxbool32
pxString32BeginsWithMemory(PxString32 self, pxword32* memory, pxint length);

pxbool32
pxString32EndsWith(PxString32 self, PxString32 value);

pxbool32
pxString32EndsWithMemory(PxString32 self, pxword32* memory, pxint length);

pxint
pxString32Contains(PxString32 self, PxString32 value);

pxint
pxString32ContainsMemory(PxString32 self, pxword32* memory, pxint length);

PxString32
pxString32Slice(PxString32 self, pxint start, pxint stop);

PxString32
pxString32SliceLength(PxString32 self, pxint index, pxint length);

PxString32
pxString32TrimSpaces(PxString32 self);

PxString32
pxString32TrimSpacesHead(PxString32 self);

PxString32
pxString32TrimSpacesTail(PxString32 self);

PxString32
pxString32TrimPrefix(PxString32 self, PxString32 prefix);

PxString32
pxString32TrimPrefixMemory(PxString32 self, pxword32* memory, pxint length);

PxString32
pxString32TrimSuffix(PxString32 self, PxString32 suffix);

PxString32
pxString32TrimSuffixMemory(PxString32 self, pxword32* memory, pxint length);

pxbool32
pxString32FindFirst(PxString32 self, pxint start, PxString32 value, pxint* index);

pxbool32
pxString32FindFirstMemory(PxString32 self, pxint start, pxword32* memory, pxint length, pxint* index);

pxbool32
pxString32FindLast(PxString32 self, pxint start, PxString32 value, pxint* index);

pxbool32
pxString32FindLastMemory(PxString32 self, pxint start, pxword32* memory, pxint length, pxint* index);

pxbool32
pxString32Split(PxString32 self, PxString32 pivot, PxString32* left, PxString32* right);

pxbool32
pxString32SplitMemory(PxString32 self, pxword32* memory, pxint length, PxString32* left, PxString32* right);

pxbool32
pxString32Next(PxString32 self, pxint index, pxint* units, pxint32* value);

pxbool32
pxString32Prev(PxString32 self, pxint index, pxint* units, pxint32* value);

#endif // PX_STRING_STRING32_H
