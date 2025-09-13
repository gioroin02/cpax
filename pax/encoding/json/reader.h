#ifndef PX_ENCODING_JSON_READER_H
#define PX_ENCODING_JSON_READER_H

#include "token.h"
#include "event.h"

typedef struct PxJsonReader
{
    PxQueue   stack;
    PxString8 name;
    pxb8      colon;
    pxb8      comma;

    PxReader* reader;
}
PxJsonReader;

PxJsonReader
pxJsonReaderMake(PxArena* arena, pxiword length, PxReader* reader);

PxJsonEvent
pxJsonReaderNext(PxJsonReader* self, PxArena* arena);

#endif // PX_ENCODING_JSON_READER_H
