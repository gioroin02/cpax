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

pxu8
pxConsoleSequenceSetFunction(PxConsoleSequence* self, pxu8 value);

pxb8
pxConsoleSequenceAddArgument(PxConsoleSequence* self, pxu8 value);

pxiword
pxConsoleSequenceFromString8(PxConsoleSequence* self, PxString8 string);

#endif // PX_CORE_CONSOLE_SEQUENCE_H
