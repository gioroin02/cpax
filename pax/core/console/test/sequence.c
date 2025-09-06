#include "../export.h"

#include <stdio.h>

int
main(int argc, char** argv)
{
    PxConsoleSequence sequence = {0};

    pxConsoleSequenceFromString8(&sequence, pxs8("\x1b[A"));
}
