#include "../export.h"

#include <stdio.h>

int
main(int argc, char** argv)
{
    PxConsoleSequence sequence = {0};

    pxb8 state = pxConsoleSequenceFromString8(
        &sequence, pxs8("\x1b[5~"));

    if (state == 0) return 1;

    printf("func = %c\n", sequence.func);

    for (pxiword i = 0; i < sequence.size; i += 1)
        printf("args = %u\n", sequence.args[i]);
}
