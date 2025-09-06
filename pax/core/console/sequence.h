#ifndef PX_CORE_CONSOLE_SEQUENCE_H
#define PX_CORE_CONSOLE_SEQUENCE_H

#include "event.h"

#define PX_CONSOLE_SEQUENCE_ARGS 16

typedef struct PxConsoleSequence
{
    pxu8    func;
    pxu8    args[PX_CONSOLE_SEQUENCE_ARGS];
    pxiword size;
}
PxConsoleSequence;

pxb8
pxConsoleSequenceFromString8(PxConsoleSequence* self, PxString8 string);

PxConsoleEvent
pxConsoleEventFromSequence(PxConsoleSequence* self);

#endif // PX_CORE_CONSOLE_SEQUENCE_H
