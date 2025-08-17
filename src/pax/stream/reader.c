#ifndef PX_STREAM_READER_C
#define PX_STREAM_READER_C

#include "reader.h"

PxReader
pxBufferReader(PxBuffer8* self, PxBuffer8* buffer)
{
    if (self == 0 || buffer == 0)
        return (PxReader) {0};

    return (PxReader) {
        .buffer = buffer,
        .ctxt   = self,
        .proc   = &pxBuffer8ReadHead,
    };
}

PxBuffer8*
pxReaderSetBuffer(PxReader* self, PxBuffer8* buffer)
{
    PxBuffer8* result = self->buffer;

    if (buffer != 0)
        self->buffer = buffer;
    else
        return 0;

    return result;
}

pxint
pxReaderFill(PxReader* self)
{
    PxReaderProc* proc = pxCast(PxReaderProc*, self->proc);

    if (proc != 0)
        return proc(self->ctxt, self->buffer);

    return 0;
}

pxword8
pxReaderDrop(PxReader* self, pxint offset)
{
    if (offset < 0) return 0;

    for (pxint i = 0; i < offset;) {
        i += pxBuffer8DropHead(self->buffer, offset - i);

        if (pxReaderFill(self) == 0) {
            if (i >= offset)
                break;

            return 0;
        }
    }

    return pxBuffer8GetForwOr(self->buffer, 0, 0);
}

pxword8
pxReaderPeek(PxReader* self, pxint offset)
{
    if (offset < 0) return 0;

    if (offset >= self->buffer->size) {
        if (offset >= self->buffer->length) return 0;

        for (pxint i = 0; i < offset - self->buffer->size + 1;) {
            pxint amount = pxReaderFill(self);

            if (amount != 0)
                i += amount;
            else
                return 0;
        }
    }

    return pxBuffer8GetForwOr(self->buffer, offset, 0);
}

PxString8
pxReaderPeekString(PxReader* self, PxArena* arena, pxint length)
{
    if (length <= 0) return (PxString8) {0};

    if (length > self->buffer->size) {
        if (length > self->buffer->length) return (PxString8) {0};

        for (pxint i = 0; i < length - self->buffer->size;) {
            pxint amount = pxReaderFill(self);

            if (amount != 0)
                i += amount;
            else
                return (PxString8) {0};
        }
    }

    return pxBuffer8PeekStringHead(self->buffer, arena, length);
}

PxString8
pxReaderPeekLine(PxReader* self, PxArena* arena, pxint length)
{
    if (length <= 0) return (PxString8) {0};

    pxint   diff = 0;
    pxword8 word = pxReaderPeek(self, diff);

    while (word != 0 && word != 10 && diff <= length) {
        diff += 1;
        word  = pxReaderPeek(self, diff);
    }

    return pxReaderPeekString(self, arena, diff);
}

PxString8
pxReaderString(PxReader* self, PxArena* arena, pxint length)
{
    if (length <= 0) return (PxString8) {0};

    pxint    offset = pxArenaOffset(arena);
    pxword8* result = pxArenaReserve(arena, pxword8, length + 1);

    if (result == 0) return (PxString8) {0};

    for (pxint i = 0; i < length;) {
        i += pxBuffer8ReadMemoryHead(self->buffer,
            result + i, length - i);

        if (pxReaderFill(self) == 0) {
            if (i < length)
                pxArenaRewind(arena, offset);
            else
                break;

            return (PxString8) {0};
        }
    }

    return (PxString8) {
        .memory = result,
        .length = length,
    };
}

PxString8
pxReaderLine(PxReader* self, PxArena* arena, pxint length)
{
    if (length <= 0) return (PxString8) {0};

    pxint    offset = pxArenaOffset(arena);
    pxword8* result = pxArenaReserve(arena, pxword8, length + 1);
    pxint    diff   = 0;
    pxword8  word   = pxReaderPeek(self, diff);

    if (result == 0) return (PxString8) {0};

    while (word != 0 && word != 10 && diff <= length) {
        result[diff] = word;

        diff += 1;
        word  = pxReaderPeek(self, diff);
    }

    if (diff < length) pxArenaRewind(arena, offset + diff + 1);

    return (PxString8) {
        .memory = result,
        .length = diff,
    };
}

#endif // PX_STREAM_READER_C
