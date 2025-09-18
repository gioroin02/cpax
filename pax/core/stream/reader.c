#ifndef PX_CORE_STREAM_READER_C
#define PX_CORE_STREAM_READER_C

#include "reader.h"

PxReader
pxReaderFromInput(PxInput input, PxArena* arena, pxiword length)
{
    PxReader result = {0};

    result.buffer = pxBuffer8Reserve(arena, length);

    if (result.buffer.length > 0)
        result.input = input;

    return result;
}

pxiword
pxReaderFill(PxReader* self)
{
    return pxInputBuffer8(self->input, &self->buffer);
}

pxiword
pxReaderSkip(PxReader* self, pxiword amount)
{
    pxiword result = 0;

    if (amount <= 0) return result;

    while (result < amount) {
        if (self->buffer.size <= 0 && pxReaderFill(self) <= 0)
            return result;

        result += pxBuffer8DropHead(&self->buffer,
            amount - result);
    }

    return amount;
}

pxiword
pxReaderMemory8(PxReader* self, pxu8* memory, pxiword length, pxiword index)
{
    pxiword temp = pxReaderSkip(self, index);

    if (temp < index) return temp;

    if (self->buffer.size <= 0) pxReaderFill(self);

    pxiword size =
        pxBuffer8ReadMemory8Head(&self->buffer, memory, length);

    return index + size;
}

pxiword
pxReaderMemory8Peek(PxReader* self, pxu8* memory, pxiword length, pxiword index)
{
    if (self->buffer.size <= 0) pxReaderFill(self);

    pxiword size = pxmin(self->buffer.size - index, length);

    for (pxiword i = 0; i < size; i += 1)
        memory[i] = pxBuffer8GetForwOr(&self->buffer, i + index, 0);

    return size;
}

pxiword
pxReaderByte(PxReader* self, pxu8* value, pxiword index)
{
    return pxReaderMemory8(self, value, 1, index);
}

pxiword
pxReaderBytePeek(PxReader* self, pxu8* value, pxiword index)
{
    return pxReaderMemory8Peek(self, value, 1, index);
}

PxString8
pxReaderString8(PxReader* self, PxArena* arena, pxiword length, pxiword index)
{
    pxiword offset = pxArenaOffset(arena);
    pxu8*   memory = pxArenaReserve(arena, pxu8, length + 1);

    pxiword size = pxReaderMemory8(self, memory, length, index);

    pxArenaRewind(arena, offset + size - index + 1);

    return pxString8Make(memory, size);
}

PxString8
pxReaderString8Peek(PxReader* self, PxArena* arena, pxiword length, pxiword index)
{
    pxiword offset = pxArenaOffset(arena);
    pxu8*   memory = pxArenaReserve(arena, pxu8, length + 1);

    pxiword size = pxReaderMemory8Peek(self, memory, length, index);

    pxArenaRewind(arena, offset + size - index + 1);

    return pxString8Make(memory, size);
}

#endif // PX_CORE_STREAM_READER_C
