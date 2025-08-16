#ifndef PX_STRING_STRING8_H
#define PX_STRING_STRING8_H

#include "utf8.h"

typedef struct
{
    pxword8* memory;
    pxint length;
}
PxString8;

PxString8
pxString8FromUnicode(PxArena* arena, pxint32 value);

PxString8
pxString8Copy(PxArena* arena, PxString8 string);

PxString8
pxString8CopyMemory(PxArena* arena, pxword8* memory, pxint length);

PxString8
pxString8Chain(PxString8 self, PxArena* arena, PxString8 value);

PxString8
pxString8ChainMemory(PxString8 self, PxArena* arena, pxword8* memory, pxint length);

pxbool8
pxString8Get(PxString8 self, pxint index, pxword8* value);

pxword8
pxString8GetOr(PxString8 self, pxint index, pxword8 value);

pxbool8
pxString8IsEqual(PxString8 self, PxString8 value);

pxbool8
pxString8IsEqualMemory(PxString8 self, pxword8* memory, pxint length);

pxbool8
pxString8BeginsWith(PxString8 self, PxString8 value);

pxbool8
pxString8BeginsWithMemory(PxString8 self, pxword8* memory, pxint length);

pxbool8
pxString8EndsWith(PxString8 self, PxString8 value);

pxbool8
pxString8EndsWithMemory(PxString8 self, pxword8* memory, pxint length);

pxint
pxString8Contains(PxString8 self, PxString8 value);

pxint
pxString8ContainsMemory(PxString8 self, pxword8* memory, pxint length);

PxString8
pxString8Slice(PxString8 self, pxint start, pxint stop);

PxString8
pxString8SliceLength(PxString8 self, pxint index, pxint length);

PxString8
pxString8TrimSpaces(PxString8 self);

PxString8
pxString8TrimSpacesHead(PxString8 self);

PxString8
pxString8TrimSpacesTail(PxString8 self);

PxString8
pxString8TrimPrefix(PxString8 self, PxString8 prefix);

PxString8
pxString8TrimPrefixMemory(PxString8 self, pxword8* memory, pxint length);

PxString8
pxString8TrimSuffix(PxString8 self, PxString8 suffix);

PxString8
pxString8TrimSuffixMemory(PxString8 self, pxword8* memory, pxint length);

pxbool8
pxString8FindFirst(PxString8 self, pxint start, PxString8 value, pxint* index);

pxbool8
pxString8FindFirstMemory(PxString8 self, pxint start, pxword8* memory, pxint length, pxint* index);

pxbool8
pxString8FindLast(PxString8 self, pxint start, PxString8 value, pxint* index);

pxbool8
pxString8FindLastMemory(PxString8 self, pxint start, pxword8* memory, pxint length, pxint* index);

pxbool8
pxString8Split(PxString8 self, PxString8 pivot, PxString8* left, PxString8* right);

pxbool8
pxString8SplitMemory(PxString8 self, pxword8* memory, pxint length, PxString8* left, PxString8* right);

#endif // PX_STRING_STRING8_H
