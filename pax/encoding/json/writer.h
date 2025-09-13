#ifndef PX_ENCODING_JSON_WRITER_H
#define PX_ENCODING_JSON_WRITER_H

#include "event.h"

typedef struct PxJsonWriter
{
    PxQueue stack;
    pxb8    comma;

    PxWriter* writer;
}
PxJsonWriter;

PxJsonWriter
pxJsonWriterMake(PxArena* arena, pxiword length, PxWriter* writer);

pxb8
pxJsonWriterNext(PxJsonWriter* self, PxArena* arena, PxJsonEvent event);

#endif // PX_ENCODING_JSON_WRITER_H
