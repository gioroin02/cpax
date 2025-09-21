#ifndef PX_CORE_STREAM_READER_H
#define PX_CORE_STREAM_READER_H

#include "input.h"

#define pxReaderMemory8Line(self, memory, length, index) \
    pxReaderMemory8(self, memory, length, index, PX_ASCII_LINE_FEED)

#define pxReaderString8Line(self, arena, length, index) \
    pxReaderString8(self, arena, length, index, PX_ASCII_LINE_FEED)

#define pxReaderPeekMemory8Line(self, memory, length, index) \
    pxReaderPeekMemory8(self, memory, length, index, PX_ASCII_LINE_FEED)

#define pxReaderPeekString8Line(self, arena, length, index) \
    pxReaderPeekString8(self, arena, length, index, PX_ASCII_LINE_FEED)

typedef struct PxReader
{
    PxBuffer8 buffer;
    PxInput   input;
}
PxReader;

PxReader
pxReaderFromInput(PxInput input, PxArena* arena, pxiword length);

pxiword
pxReaderFill(PxReader* self);

pxu8
pxReaderByte(PxReader* self, pxiword index);

pxiword
pxReaderMemory8(PxReader* self, pxu8* memory, pxiword length, pxiword index, pxu8 pivot);

pxiword
pxReaderBuffer8(PxReader* self, PxBuffer8* value, pxiword index, pxu8 pivot);

PxString8
pxReaderString8(PxReader* self, PxArena* arena, pxiword length, pxiword index, pxu8 pivot);

pxu8
pxReaderPeekByte(PxReader* self, pxiword index);

pxiword
pxReaderPeekMemory8(PxReader* self, pxu8* memory, pxiword length, pxiword index, pxu8 pivot);

pxiword
pxReaderPeekBuffer8(PxReader* self, PxBuffer8* value, pxiword index, pxu8 pivot);

PxString8
pxReaderPeekString8(PxReader* self, PxArena* arena, pxiword length, pxiword index, pxu8 pivot);

pxiword
pxReaderSkip(PxReader* self, pxiword amount);

#endif // PX_CORE_STREAM_READER_H
