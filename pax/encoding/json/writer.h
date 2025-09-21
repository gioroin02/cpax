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

typedef pxb8 (PxJsonWriterProc) (void*, PxJsonWriter*, PxArena*);

PxJsonWriter
pxJsonWriterReserve(PxArena* arena, pxiword length, PxWriter* writer);

pxb8
pxJsonWriterMsg(PxJsonWriter* self, PxArena* arena, PxJsonMsg message);

pxiword
pxJsonWriterList(PxJsonWriter* self, PxArena* arena, PxJsonMsg* values, pxiword length);

pxb8
pxJsonWriterObjectItem(PxJsonWriter* self, PxArena* arena, void* ctxt, void* proc, PxString8 name);

pxb8
pxJsonWriterObjectOpen(PxJsonWriter* self, PxArena* arena);

pxb8
pxJsonWriterObjectClose(PxJsonWriter* self, PxArena* arena);

pxb8
pxJsonWriterArrayItem(PxJsonWriter* self, PxArena* arena, void* ctxt, void* proc);

pxb8
pxJsonWriterArrayOpen(PxJsonWriter* self, PxArena* arena);

pxb8
pxJsonWriterArrayClose(PxJsonWriter* self, PxArena* arena);

#endif // PX_ENCODING_JSON_WRITER_H
