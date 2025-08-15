#ifndef PX_STREAM_BUF8_H
#define PX_STREAM_BUF8_H

#include "import.h"

typedef struct
{
    pxn8* memory;
    pxint length;
    pxint size;
    pxint head;
    pxint tail;
}
PxBuffer8;

/* PxBuffer8 */

PxBuffer8
pxBuffer8Make(pxn8* memory, pxint length);

PxBuffer8
pxBuffer8MakeFull(pxn8* memory, pxint length);

PxBuffer8
pxBuffer8Reserve(PxArena* arena, pxint length);

PxBuffer8
pxBuffer8ReserveFull(PxArena* arena, pxint length);

PxBuffer8
pxBuffer8Copy(PxArena* arena, PxBuffer8 value);

PxBuffer8
pxBuffer8CopyAmount(PxArena* arena, PxBuffer8 value, pxint amount);

PxBuffer8
pxBuffer8CopyMemory(PxArena* arena, pxn8* memory, pxint length);

void
pxBuffer8Clear(PxBuffer8* self);

void
pxBuffer8Fill(PxBuffer8* self);

void
pxBuffer8Normalize(PxBuffer8* self);

/* PxBuffer8 getting */

pxb8
pxBuffer8GetForw(PxBuffer8* self, pxint index, pxn8* value);

pxn8
pxBuffer8GetForwOr(PxBuffer8* self, pxint index, pxn8 value);

pxb8
pxBuffer8GetBack(PxBuffer8* self, pxint index, pxn8* value);

pxn8
pxBuffer8GetBackOr(PxBuffer8* self, pxint index, pxn8 value);

/* PxBuffer8 dropping */

pxint
pxBuffer8DropHead(PxBuffer8* self, pxint amount);

pxint
pxBuffer8DropTail(PxBuffer8* self, pxint amount);

/* PxBuffer8 writing */

pxint
pxBuffer8WriteHead(PxBuffer8* self, PxBuffer8* buffer);

pxint
pxBuffer8WriteMemory8Head(PxBuffer8* self, pxn8* memory, pxint length);

pxint
pxBuffer8WriteTail(PxBuffer8* self, PxBuffer8* buffer);

pxint
pxBuffer8WriteMemory8Tail(PxBuffer8* self, pxn8* memory, pxint length);

/* PxBuffer8 reading */

pxint
pxBuffer8ReadHead(PxBuffer8* self, PxBuffer8* buffer);

pxint
pxBuffer8ReadMemory8Head(PxBuffer8* self, pxn8* memory, pxint length);

pxint
pxBuffer8ReadTail(PxBuffer8* self, PxBuffer8* buffer);

pxint
pxBuffer8ReadMemory8Tail(PxBuffer8* self, pxn8* memory, pxint length);

/* PxBuffer8 peeking */

pxint
pxBuffer8PeekHead(PxBuffer8* self, PxBuffer8* buffer);

pxint
pxBuffer8PeekMemory8Head(PxBuffer8* self, pxn8* memory, pxint length);

pxint
pxBuffer8PeekTail(PxBuffer8* self, PxBuffer8* buffer);

pxint
pxBuffer8PeekMemory8Tail(PxBuffer8* self, pxn8* memory, pxint length);

#endif // PX_STREAM_BUF8_H
