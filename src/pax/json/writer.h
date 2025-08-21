#ifndef PX_JSON_WRITER_H
#define PX_JSON_WRITER_H

#include "event.h"

typedef struct PxJsonWriter
{
    PxWriter writer;
    PxQueue  stack;

    pxb8 comma;
}
PxJsonWriter;

PxJsonWriter
pxJsonWriterMake(PxArena* arena, pxint length, PxWriter writer);

pxb8
pxJsonWriterNext(PxJsonWriter* self, PxArena* arena, PxJsonEvent event);

#endif // PX_JSON_WRITER_H
