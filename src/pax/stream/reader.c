#ifndef PX_STREAM_READER_C
#define PX_STREAM_READER_C

#include "reader.h"

PxReader
pxReaderFromBuffer8(PxBuffer8* buffer)
{
    if (buffer == 0)
        return (PxReader) {0};

    return (PxReader) {
        .ctxt = buffer,
        .proc = &pxBuffer8ReadHead,
    };
}

pxint
pxReaderFill(PxReader self, PxBuffer8* buffer)
{
    PxReaderProc* proc = pxCast(PxReaderProc*, self.proc);

    if (proc != 0)
        return proc(self.ctxt, buffer);

    return 0;
}

pxword8
pxReaderPeek(PxReader self, PxBuffer8* buffer, pxint offset)
{
    if (offset < 0) return 0;

    if (offset >= buffer->size) {
        if (offset >= buffer->length) return 0;

        pxint target = offset - buffer->size + 1;
        pxint amount = 0;

        for (pxint i = 0; i < target; i += amount) {
            amount = pxReaderFill(self, buffer);

            if (amount == 0)
                return 0;
        }
    }

    return pxBuffer8GetForwOr(buffer, offset, 0);
}

pxword8
pxReaderMove(PxReader self, PxBuffer8* buffer, pxint offset)
{
    if (offset < 0) return 0;

    while (offset >= buffer->size) {
        offset -= pxBuffer8DropHead(buffer, buffer->size);

        if (pxReaderFill(self, buffer) == 0)
            return 0;
    }

    pxBuffer8DropHead(buffer, offset);

    return pxBuffer8GetForwOr(buffer, 0, 0);
}

#endif // PX_STREAM_READER_C
