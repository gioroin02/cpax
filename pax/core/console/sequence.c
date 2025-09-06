#ifndef PX_CORE_CONSOLE_SEQUENCE_C
#define PX_CORE_CONSOLE_SEQUENCE_C

#include "sequence.h"

pxb8
pxConsoleSequenceFromString8(PxConsoleSequence* self, PxString8 string)
{
    pxiword index = 1;

    if (string.length <= 1 || string.memory[0] != 0x1b)
        return 0;

    return 1;
}

#endif // PX_CORE_CONSOLE_SEQUENCE_C
