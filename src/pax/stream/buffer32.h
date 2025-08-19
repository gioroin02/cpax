#ifndef PX_STREAM_BUFFER32_H
#define PX_STREAM_BUFFER32_H

#include "import.h"

typedef struct PxBuffer32
{
    pxu32* memory;
    pxint  length;
    pxint  size;
    pxint  head;
    pxint  tail;
}
PxBuffer32;

/* PxBuffer32 */

PxBuffer32
pxBuffer32Make(pxu32* memory, pxint length);

PxBuffer32
pxBuffer32MakeFull(pxu32* memory, pxint length);

PxBuffer32
pxBuffer32Reserve(PxArena* arena, pxint length);

PxBuffer32
pxBuffer32ReserveFull(PxArena* arena, pxint length);

PxBuffer32
pxBuffer32Copy(PxArena* arena, PxBuffer32 value);

PxBuffer32
pxBuffer32CopyAmount(PxArena* arena, PxBuffer32 value, pxint amount);

PxBuffer32
pxBuffer32CopyMemory(PxArena* arena, pxu32* memory, pxint length);

void
pxBuffer32Clear(PxBuffer32* self);

void
pxBuffer32Fill(PxBuffer32* self);

void
pxBuffer32Normalize(PxBuffer32* self);

/* PxBuffer32 getting */

pxb8
pxBuffer32GetForw(PxBuffer32* self, pxint index, pxu32* value);

pxu32
pxBuffer32GetForwOr(PxBuffer32* self, pxint index, pxu32 value);

pxb8
pxBuffer32GetBack(PxBuffer32* self, pxint index, pxu32* value);

pxu32
pxBuffer32GetBackOr(PxBuffer32* self, pxint index, pxu32 value);

/* PxBuffer32 dropping */

pxint
pxBuffer32DropHead(PxBuffer32* self, pxint amount);

pxint
pxBuffer32DropTail(PxBuffer32* self, pxint amount);

/* PxBuffer32 writing */

pxint
pxBuffer32WriteHead(PxBuffer32* self, PxBuffer32* buffer);

pxint
pxBuffer32WriteMemoryHead(PxBuffer32* self, pxu32* memory, pxint length);

pxint
pxBuffer32WriteStringHead(PxBuffer32* self, PxString32 string);

pxint
pxBuffer32WriteTail(PxBuffer32* self, PxBuffer32* buffer);

pxint
pxBuffer32WriteMemoryTail(PxBuffer32* self, pxu32* memory, pxint length);

pxint
pxBuffer32WriteStringTail(PxBuffer32* self, PxString32 string);

/* PxBuffer32 reading */

pxint
pxBuffer32ReadHead(PxBuffer32* self, PxBuffer32* buffer);

pxint
pxBuffer32ReadMemoryHead(PxBuffer32* self, pxu32* memory, pxint length);

PxString32
pxBuffer32ReadStringHead(PxBuffer32* self, PxArena* arena, pxint length);

pxint
pxBuffer32ReadTail(PxBuffer32* self, PxBuffer32* buffer);

pxint
pxBuffer32ReadMemoryTail(PxBuffer32* self, pxu32* memory, pxint length);

PxString32
pxBuffer32ReadStringTail(PxBuffer32* self, PxArena* arena, pxint length);

/* PxBuffer32 peeking */

pxint
pxBuffer32PeekHead(PxBuffer32* self, PxBuffer32* buffer);

pxint
pxBuffer32PeekMemoryHead(PxBuffer32* self, pxu32* memory, pxint length);

PxString32
pxBuffer32PeekStringHead(PxBuffer32* self, PxArena* arena, pxint length);

pxint
pxBuffer32PeekTail(PxBuffer32* self, PxBuffer32* buffer);

pxint
pxBuffer32PeekMemoryTail(PxBuffer32* self, pxu32* memory, pxint length);

PxString32
pxBuffer32PeekStringTail(PxBuffer32* self, PxArena* arena, pxint length);

#endif // PX_STREAM_BUFFER32_H
