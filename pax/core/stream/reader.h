#ifndef PX_CORE_STREAM_READER_H
#define PX_CORE_STREAM_READER_H

#include "input.h"

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

pxiword
pxReaderSkip(PxReader* self, pxiword amount);

pxiword
pxReaderMemory8(PxReader* self, pxu8* memory, pxiword length, pxiword index);

pxiword
pxReaderMemory8Peek(PxReader* self, pxu8* memory, pxiword length, pxiword index);

pxiword
pxReaderByte(PxReader* self, pxu8* value, pxiword index);

pxiword
pxReaderBytePeek(PxReader* self, pxu8* value, pxiword index);

PxString8
pxReaderString8(PxReader* self, PxArena* arena, pxiword length, pxiword index);

PxString8
pxReaderString8Peek(PxReader* self, PxArena* arena, pxiword length, pxiword index);

#endif // PX_CORE_STREAM_READER_H
