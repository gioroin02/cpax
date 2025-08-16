#ifndef PX_STREAM_BUF8_C
#define PX_STREAM_BUF8_C

#include "buffer8.h"

PxBuffer8
pxBuffer8Make(pxword8* memory, pxint length)
{
    if (memory == 0 || length <= 0)
        return (PxBuffer8) {0};

    return (PxBuffer8) {
        .memory = memory,
        .length = length,
    };
}

PxBuffer8
pxBuffer8MakeFull(pxword8* memory, pxint length)
{
    if (memory == 0 || length <= 0)
        return (PxBuffer8) {0};

    return (PxBuffer8) {
        .memory = memory,
        .length = length,
        .size   = length,
        .tail   = length,
    };
}

PxBuffer8
pxBuffer8Reserve(PxArena* arena, pxint length)
{
    pxword8* memory =
        pxArenaReserveManyOf(arena, pxword8, length);

    return pxBuffer8Make(memory, length);
}

PxBuffer8
pxBuffer8ReserveFull(PxArena* arena, pxint length)
{
    pxword8* memory =
        pxArenaReserveManyOf(arena, pxword8, length);

    return pxBuffer8MakeFull(memory, length);
}

PxBuffer8
pxBuffer8Copy(PxArena* arena, PxBuffer8 value)
{
    return pxBuffer8CopyAmount(arena, value, value.length);
}

PxBuffer8
pxBuffer8CopyAmount(PxArena* arena, PxBuffer8 value, pxint length)
{
    PxBuffer8 result = pxBuffer8Reserve(arena, length);

    if (result.length <= 0) return result;

    result.size = pxMin(result.length, value.size);
    result.tail = result.size;

    for (pxint i = 0; i < result.size; i += 1)
        result.memory[i] = value.memory[(value.head + i) % value.length];

    return result;
}

PxBuffer8
pxBuffer8CopyMemory(PxArena* arena, pxword8* memory, pxint length)
{
    PxBuffer8 result = pxBuffer8Reserve(arena, length);

    if (result.length <= 0) return result;

    result.size = result.length;
    result.tail = result.length;

    pxMemoryCopy(result.memory, memory, result.size, 1);

    return result;
}

void
pxBuffer8Clear(PxBuffer8* self)
{
    self->size = 0;
    self->head = 0;
    self->tail = 0;
}

void
pxBuffer8Fill(PxBuffer8* self)
{
    pxint diff = self->length - self->size;

    self->size = self->length;
    self->tail = self->head;

    for (pxint i = 0; i < diff; i += 1)
        self->memory[(self->head + i) % self->length] = 0;
}

void
pxBuffer8Normalize(PxBuffer8* self);

pxbool8
pxBuffer8GetForw(PxBuffer8* self, pxint index, pxword8* value)
{
    if (index < 0 || index >= self->size)
        return 0;

    index = (self->head + index) % self->length;

    if (value != 0)
        *value = self->memory[index];

    return 1;
}

pxword8
pxBuffer8GetForwOr(PxBuffer8* self, pxint index, pxword8 value)
{
    if (index < 0 || index >= self->size)
        return value;

    index = (self->head + index) % self->length;

    return self->memory[index];
}

pxbool8
pxBuffer8GetBack(PxBuffer8* self, pxint index, pxword8* value)
{
    if (index < 0 || index >= self->size)
        return 0;

    index = (self->tail + self->length - index) % self->length;

    if (value != 0)
        *value = self->memory[index];

    return 1;
}

pxword8
pxBuffer8GetBackOr(PxBuffer8* self, pxint index, pxword8 value)
{
    if (index < 0 || index >= self->size)
        return value;

    index = (self->tail + self->length - index) % self->length;

    return self->memory[index];
}

pxint
pxBuffer8DropHead(PxBuffer8* self, pxint amount)
{
    amount = pxMin(amount, self->size);

    if (amount > 0) {
        pxint next = self->head + amount;

        self->size -= amount;
        self->head  = next % self->length;
    }

    return amount;
}

pxint
pxBuffer8DropTail(PxBuffer8* self, pxint amount)
{
    amount = pxMin(amount, self->size);

    if (amount > 0) {
        pxint prev = self->tail + self->length - amount;

        self->size -= amount;
        self->tail  = prev % self->length;
    }

    return amount;
}

pxint
pxBuffer8WriteHead(PxBuffer8* self, PxBuffer8* buffer);

pxint
pxBuffer8WriteMemoryHead(PxBuffer8* self, pxword8* memory, pxint length);

pxint
pxBuffer8WriteTail(PxBuffer8* self, PxBuffer8* buffer)
{
    pxint size = pxMin(buffer->size, self->length - self->size);

    if (size <= 0 || size > self->length) return 0;

    pxint next = self->tail + size;

    for (pxint i = 0; i < size; i += 1) {
        self->memory[(self->tail + i) % self->length] =
            buffer->memory[(buffer->head + i) % buffer->length];
    }

    self->size += size;
    self->tail  = next % self->length;

    buffer->size -= size;
    buffer->head  = (buffer->head + size) % buffer->length;

    return size;
}

pxint
pxBuffer8WriteMemoryTail(PxBuffer8* self, pxword8* memory, pxint length)
{
    pxint size = pxMin(length, self->length - self->size);

    if (size <= 0 || size > self->length) return 0;

    pxint next = self->tail + size;

    for (pxint i = 0; i < size; i += 1)
        self->memory[(self->tail + i) % self->length] = memory[i];

    self->size += size;
    self->tail  = next % self->length;

    return size;
}

pxint
pxBuffer8ReadHead(PxBuffer8* self, PxBuffer8* buffer)
{
    pxint size = pxMin(self->size, buffer->length - buffer->size);

    if (size <= 0 || size > self->size) return 0;

    pxint next = self->head + size;

    for (pxint i = 0; i < size; i += 1) {
        buffer->memory[(buffer->tail + i) % buffer->length] =
            self->memory[(self->head + i) % self->length];
    }

    self->size -= size;
    self->head  = next % self->length;

    buffer->size += size;
    buffer->tail  = (buffer->tail + size) % buffer->length;

    return size;
}

pxint
pxBuffer8ReadMemoryHead(PxBuffer8* self, pxword8* memory, pxint length)
{
    pxint size = pxMin(self->size, length);

    if (size <= 0 || size > self->size) return 0;

    pxint next = self->head + size;

    for (pxint i = 0; i < size; i += 1)
        memory[i] = self->memory[(self->head + i) % self->length];

    self->size -= size;
    self->head  = next % self->length;

    return size;
}

pxint
pxBuffer8ReadTail(PxBuffer8* self, PxBuffer8* buffer);

pxint
pxBuffer8ReadMemoryTail(PxBuffer8* self, pxword8* memory, pxint length);

pxint
pxBuffer8PeekHead(PxBuffer8* self, PxBuffer8* buffer);

pxint
pxBuffer8PeekMemoryHead(PxBuffer8* self, pxword8* memory, pxint length);

pxint
pxBuffer8PeekTail(PxBuffer8* self, PxBuffer8* buffer);

pxint
pxBuffer8PeekMemoryTail(PxBuffer8* self, pxword8* memory, pxint length);

#endif // PX_STREAM_BUF8_C
