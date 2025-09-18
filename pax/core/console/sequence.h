#ifndef PX_CORE_CONSOLE_SEQUENCE_H
#define PX_CORE_CONSOLE_SEQUENCE_H

#include "import.h"

#define PX_ESCAPE_GROUPS 8
#define PX_ESCAPE_VALUES 2

typedef struct PxAnsiSequenceGroup
{
    pxuword values[PX_ESCAPE_VALUES];
    pxiword size;
}
PxAnsiSequenceGroup;

typedef struct PxAnsiSequence
{
    PxAnsiSequenceGroup groups[PX_ESCAPE_GROUPS];
    pxiword             size;

    pxu8 func;
}
PxAnsiSequence;

pxb8
pxAnsiSequenceGroupInsert(PxAnsiSequenceGroup* self, pxuword value);

pxb8
pxAnsiSequenceRead(PxAnsiSequence* self, pxiword group, pxiword index, pxuword* value);

pxuword
pxAnsiSequenceReadOr(PxAnsiSequence* self, pxiword group, pxiword index, pxuword value);

pxb8
pxAnsiSequenceGroupFromString8(PxString8 string, PxAnsiSequenceGroup* value);

pxb8
pxAnsiSequenceFromString8(PxString8 string, PxAnsiSequence* value);

#endif // PX_CORE_CONSOLE_SEQUENCE_H
