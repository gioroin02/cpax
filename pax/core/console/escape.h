#ifndef PX_CORE_CONSOLE_ESCAPE_H
#define PX_CORE_CONSOLE_ESCAPE_H

#include "event.h"

#define PX_ESCAPE_ITEMS 16

typedef enum PxEscapeType
{
    PX_ESCAPE_NONE,
    PX_ESCAPE_KEYBOARD,
    PX_ESCAPE_GRAPHICS,
    PX_ESCAPE_MOVEMENT,
}
PxEscapeType;

typedef struct PxEscape
{
    PxEscapeType type;

    pxuword items[PX_ESCAPE_ITEMS];
    pxiword size;
}
PxEscape;

PxEscapeType
pxEscapeSetType(PxEscape* self, PxEscapeType value);

pxb8
pxEscapeInsertTail(PxEscape* self, pxuword value);

pxb8
pxEscapeRead(PxEscape* self, pxiword index, pxuword* value);

pxuword
pxEscapeReadOr(PxEscape* self, pxiword index, pxuword value);

pxb8
pxEscapeFromString8(PxEscape* self, PxString8 string, pxiword* size);

pxb8
pxEscapeItemFromString8(PxEscape* self, PxString8 string);

#endif // PX_CORE_CONSOLE_ESCAPE_H
