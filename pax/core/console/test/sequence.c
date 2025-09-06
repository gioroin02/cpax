#include "../export.h"

#include <stdio.h>

void
showSequenceFromString8(PxString8 string)
{
    PxConsoleSequence seq = {0};

    pxb8 state = pxConsoleSequenceFromString8(&seq, string);

    for (pxiword i = 0; i < string.length; i += 1) {
        printf("%03u", string.memory[i]);

        if (i + 1 < string.length)
            printf("-");
    }

    printf(" %s\n", state != 0 ? "T" : "F");

    if (state != 0) {
        printf("func = %u", seq.func);

        for (pxiword i = 0; i < seq.size; i += 1)
            printf("\narg  = %u", seq.args[i]);
    }

    printf("\n");
}

int
main(int argc, char** argv)
{
    showSequenceFromString8(pxs8("\n"));
    showSequenceFromString8(pxs8("\x1b["));
    showSequenceFromString8(pxs8("\033A"));
    showSequenceFromString8(pxs8("\x1bz"));
    showSequenceFromString8(pxs8("\x1b[1;5D"));
    showSequenceFromString8(pxs8("\x1b[A"));
    showSequenceFromString8(pxs8("\x1b[38;2;1;2;3m"));
}
