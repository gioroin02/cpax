#ifndef PX_STREAM_BUF8_H
#define PX_STREAM_BUF8_H

#include "import.h"

typedef struct PxBuffer8
{
    pxword8* memory;
    pxint    length;
    pxint    size;
    pxint    head;
    pxint    tail;
}
PxBuffer8;

/* PxBuffer8 */

PxBuffer8
pxBuffer8Make(pxword8* memory, pxint length);

PxBuffer8
pxBuffer8MakeFull(pxword8* memory, pxint length);

PxBuffer8
pxBuffer8Reserve(PxArena* arena, pxint length);

PxBuffer8
pxBuffer8ReserveFull(PxArena* arena, pxint length);

PxBuffer8
pxBuffer8Copy(PxArena* arena, PxBuffer8 value);

PxBuffer8
pxBuffer8CopyAmount(PxArena* arena, PxBuffer8 value, pxint amount);

PxBuffer8
pxBuffer8CopyMemory(PxArena* arena, pxword8* memory, pxint length);

void
pxBuffer8Clear(PxBuffer8* self);

void
pxBuffer8Fill(PxBuffer8* self);

void
pxBuffer8Normalize(PxBuffer8* self);

/* PxBuffer8 getting */

pxbool8
pxBuffer8GetForw(PxBuffer8* self, pxint index, pxword8* value);

pxword8
pxBuffer8GetForwOr(PxBuffer8* self, pxint index, pxword8 value);

pxbool8
pxBuffer8GetBack(PxBuffer8* self, pxint index, pxword8* value);

pxword8
pxBuffer8GetBackOr(PxBuffer8* self, pxint index, pxword8 value);

/* PxBuffer8 dropping */

pxint
pxBuffer8DropHead(PxBuffer8* self, pxint amount);

pxint
pxBuffer8DropTail(PxBuffer8* self, pxint amount);

/* PxBuffer8 writing */

pxint
pxBuffer8WriteHead(PxBuffer8* self, PxBuffer8* buffer);

pxint
pxBuffer8WriteMemoryHead(PxBuffer8* self, pxword8* memory, pxint length);

pxint
pxBuffer8WriteStringHead(PxBuffer8* self, PxString8 string);

pxint
pxBuffer8WriteTail(PxBuffer8* self, PxBuffer8* buffer);

pxint
pxBuffer8WriteMemoryTail(PxBuffer8* self, pxword8* memory, pxint length);

pxint
pxBuffer8WriteStringTail(PxBuffer8* self, PxString8 string);

/* PxBuffer8 reading */

pxint
pxBuffer8ReadHead(PxBuffer8* self, PxBuffer8* buffer);

pxint
pxBuffer8ReadMemoryHead(PxBuffer8* self, pxword8* memory, pxint length);

PxString8
pxBuffer8ReadStringHead(PxBuffer8* self, PxArena* arena, pxint length);

pxint
pxBuffer8ReadTail(PxBuffer8* self, PxBuffer8* buffer);

pxint
pxBuffer8ReadMemoryTail(PxBuffer8* self, pxword8* memory, pxint length);

PxString8
pxBuffer8ReadStringTail(PxBuffer8* self, PxArena* arena, pxint length);

/* PxBuffer8 peeking */

pxint
pxBuffer8PeekHead(PxBuffer8* self, PxBuffer8* buffer);

pxint
pxBuffer8PeekMemoryHead(PxBuffer8* self, pxword8* memory, pxint length);

PxString8
pxBuffer8PeekStringHead(PxBuffer8* self, PxArena* arena, pxint length);

pxint
pxBuffer8PeekTail(PxBuffer8* self, PxBuffer8* buffer);

pxint
pxBuffer8PeekMemoryTail(PxBuffer8* self, pxword8* memory, pxint length);

PxString8
pxBuffer8PeekStringTail(PxBuffer8* self, PxArena* arena, pxint length);

#endif // PX_STREAM_BUF8_H
