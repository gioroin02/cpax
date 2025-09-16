#ifndef PX_ENCODING_JSON_WRITER_H
#define PX_ENCODING_JSON_WRITER_H

#include "message.h"

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
pxJsonWriteMsg(PxJsonWriter* self, PxArena* arena, PxJsonMsg message);

pxiword
pxJsonWriteList(PxJsonWriter* self, PxArena* arena, pxiword start, pxiword stop, PxJsonMsg* list);

#endif // PX_ENCODING_JSON_WRITER_H
