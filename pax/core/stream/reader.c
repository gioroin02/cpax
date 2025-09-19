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
    return pxInputNextBuffer8(self->input, &self->buffer);
}

pxu8
pxReaderNextByte(PxReader* self, pxiword index)
{
    if (index < 0) return 0;

    if (self->buffer.size <= 0 && pxReaderFill(self) <= 0)
        return 0;

    for (pxiword i = 0; i < index;) {
        i += pxBuffer8DropHead(&self->buffer, index - i);

        if (i < index || self->buffer.size <= 0) {
            if (pxReaderFill(self) <= 0)
                return 0;
        } else
            break;
    }

    return pxBuffer8GetForwOr(&self->buffer, 0, 0);
}

pxiword
pxReaderNextMemory8(PxReader* self, pxu8* memory, pxiword length, pxiword index, pxu8 pivot)
{
    if (memory == 0 || length <= 0) return 0;

    pxReaderNextByte(self, index);

    pxu8 byte = pxReaderPeekByte(self, 0);

    for (pxiword i = 0; i < length; i += 1) {
        if (byte != 0 && byte != pivot)
            memory[i] = byte;
        else
            return i;

        byte = pxReaderNextByte(self, 1);
    }

    return length;
}

PxString8
pxReaderNextString8(PxReader* self, PxArena* arena, pxiword length, pxiword index, pxu8 pivot)
{
    pxiword offset = pxArenaOffset(arena);
    pxu8*   memory = pxArenaReserve(arena, pxu8, length + 1);

    pxiword size =
        pxReaderNextMemory8(self, memory, length, index, pivot);

    if (size < length)
        pxArenaRewind(arena, offset + size + 1);

    return pxString8Make(memory, size);
}

pxu8
pxReaderPeekByte(PxReader* self, pxiword index)
{
    if (index < 0 || index >= self->buffer.length)
        return 0;

    pxiword size = index - self->buffer.size + 1;
    pxiword temp = 0;

    if (index < self->buffer.size)
        return pxBuffer8GetForwOr(&self->buffer, index, 0);

    for (pxiword i = 0; i < size; i += temp) {
        temp = pxReaderFill(self);

        if (temp <= 0)
            return 0;
    }

    return pxBuffer8GetForwOr(&self->buffer, index, 0);
}

pxiword
pxReaderPeekMemory8(PxReader* self, pxu8* memory, pxiword length, pxiword index, pxu8 pivot)
{
    if (memory == 0 || length <= 0) return 0;

    for (pxiword i = 0; i < length; i += 1) {
        pxu8 byte = pxReaderPeekByte(self, index + i);

        if (byte != 0 && byte != pivot)
            memory[i] = byte;
        else
            return i;
    }

    return length;
}

PxString8
pxReaderPeekString8(PxReader* self, PxArena* arena, pxiword length, pxiword index, pxu8 pivot)
{
    pxiword offset = pxArenaOffset(arena);
    pxu8*   memory = pxArenaReserve(arena, pxu8, length + 1);

    pxiword size =
        pxReaderPeekMemory8(self, memory, length, index, pivot);

    if (size < length)
        pxArenaRewind(arena, offset + size + 1);

    return pxString8Make(memory, size);
}

pxiword
pxReaderSkip(PxReader* self, pxiword amount)
{
    if (amount < 0) return 0;

    for (pxiword i = 0; i < amount;) {
        i += pxBuffer8DropHead(&self->buffer, amount - i);

        if (i < amount) {
            if (pxReaderFill(self) <= 0)
                return i;
        } else
            break;
    }

    return amount;
}

#endif // PX_CORE_STREAM_READER_C
