#ifndef PX_STRING_LIST_H
#define PX_STRING_LIST_H

#include "convert.h"

typedef struct PxStringListNode
{
    pxu32*  memory;
    pxiword length;

    struct PxStringListNode* next;
}
PxStringListNode;

typedef struct PxStringList
{
    PxStringListNode* head;
    PxStringListNode* tail;

    pxiword size;
}
PxStringList;

PxStringList
pxStringListFromString8(PxArena* arena, PxString8 string, PxString8 pivot);

PxStringList
pxStringListFromString16(PxArena* arena, PxString16 string, PxString16 pivot);

PxStringList
pxStringListFromString32(PxArena* arena, PxString32 string, PxString32 pivot);

pxb8
pxStringListInsertNodeHead(PxStringList* self, PxStringListNode* value);

pxb8
pxStringListInsertString8Head(PxStringList* self, PxArena* arena, PxString8 value, PxString8 pivot);

pxb8
pxStringListInsertString16Head(PxStringList* self, PxArena* arena, PxString16 value, PxString16 pivot);

pxb8
pxStringListInsertString32Head(PxStringList* self, PxArena* arena, PxString32 value, PxString32 pivot);

pxb8
pxStringListInsertNodeTail(PxStringList* self, PxStringListNode* value);

pxb8
pxStringListInsertString8Tail(PxStringList* self, PxArena* arena, PxString8 value, PxString8 pivot);

pxb8
pxStringListInsertString16Tail(PxStringList* self, PxArena* arena, PxString16 value, PxString16 pivot);

pxb8
pxStringListInsertString32Tail(PxStringList* self, PxArena* arena, PxString32 value, PxString32 pivot);

PxString8
pxString8FromStringList(PxArena* arena, PxStringList* value, PxString8 pivot);

PxString16
pxString16FromStringList(PxArena* arena, PxStringList* value, PxString16 pivot);

PxString32
pxString32FromStringList(PxArena* arena, PxStringList* value, PxString32 pivot);

#endif // PX_STRING_LIST_H
