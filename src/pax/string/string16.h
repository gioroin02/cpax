#ifndef PX_STRING_STRING16_H
#define PX_STRING_STRING16_H

#include "utf16.h"

typedef struct PxString16
{
    pxword16* memory;
    pxint     length;
}
PxString16;

PxString16
pxString16FromUnicode(PxArena* arena, pxint32 value);

PxString16
pxString16Copy(PxArena* arena, PxString16 string);

PxString16
pxString16CopyMemory(PxArena* arena, pxword16* memory, pxint length);

PxString16
pxString16Chain(PxString16 self, PxArena* arena, PxString16 value);

PxString16
pxString16ChainMemory(PxString16 self, PxArena* arena, pxword16* memory, pxint length);

pxbool16
pxString16Get(PxString16 self, pxint index, pxword16* value);

pxword16
pxString16GetOr(PxString16 self, pxint index, pxword16 value);

pxbool16
pxString16IsEqual(PxString16 self, PxString16 value);

pxbool16
pxString16IsEqualMemory(PxString16 self, pxword16* memory, pxint length);

pxbool16
pxString16BeginsWith(PxString16 self, PxString16 value);

pxbool16
pxString16BeginsWithMemory(PxString16 self, pxword16* memory, pxint length);

pxbool16
pxString16EndsWith(PxString16 self, PxString16 value);

pxbool16
pxString16EndsWithMemory(PxString16 self, pxword16* memory, pxint length);

pxint
pxString16Contains(PxString16 self, PxString16 value);

pxint
pxString16ContainsMemory(PxString16 self, pxword16* memory, pxint length);

PxString16
pxString16Slice(PxString16 self, pxint start, pxint stop);

PxString16
pxString16SliceLength(PxString16 self, pxint index, pxint length);

PxString16
pxString16TrimSpaces(PxString16 self);

PxString16
pxString16TrimSpacesHead(PxString16 self);

PxString16
pxString16TrimSpacesTail(PxString16 self);

PxString16
pxString16TrimPrefix(PxString16 self, PxString16 prefix);

PxString16
pxString16TrimPrefixMemory(PxString16 self, pxword16* memory, pxint length);

PxString16
pxString16TrimSuffix(PxString16 self, PxString16 suffix);

PxString16
pxString16TrimSuffixMemory(PxString16 self, pxword16* memory, pxint length);

pxbool16
pxString16FindFirst(PxString16 self, pxint start, PxString16 value, pxint* index);

pxbool16
pxString16FindFirstMemory(PxString16 self, pxint start, pxword16* memory, pxint length, pxint* index);

pxbool16
pxString16FindLast(PxString16 self, pxint start, PxString16 value, pxint* index);

pxbool16
pxString16FindLastMemory(PxString16 self, pxint start, pxword16* memory, pxint length, pxint* index);

pxbool16
pxString16Split(PxString16 self, PxString16 pivot, PxString16* left, PxString16* right);

pxbool16
pxString16SplitMemory(PxString16 self, pxword16* memory, pxint length, PxString16* left, PxString16* right);

pxbool16
pxString16Next(PxString16 self, pxint index, pxint* units, pxint32* value);

pxbool16
pxString16Prev(PxString16 self, pxint index, pxint* units, pxint32* value);

#endif // PX_STRING_STRING16_H
