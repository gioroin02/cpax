#include "../export.h"

#include <stdio.h>

void
showSequenceFromString8(PxString8 string)
{
    PxConsoleSequence seq = {0};

    pxiword length = pxConsoleSequenceFromString8(&seq, string);

    printf("\x1b[34m'");

    for (pxiword i = 0; i < string.length; i += 1) {
        pxu8 byte = string.memory[i];

        if (byte > 32 && byte < 128)
            printf("%c", string.memory[i]);
        else
            printf("\\x%02x", string.memory[i]);

        if (i + 1 < string.length)
            printf(" ");
    }

    printf("'\x1b[0m -> ");

    printf("func = %u", seq.func);

    for (pxiword i = 0; i < seq.size; i += 1)
        printf(", arg = %u", seq.args[i]);

    printf("\n");
}

int
main(int argc, char** argv)
{
    showSequenceFromString8(pxs8("\n"));
    showSequenceFromString8(pxs8("\033["));
    showSequenceFromString8(pxs8("\033[\0331;6A"));
    showSequenceFromString8(pxs8("\033A"));
    showSequenceFromString8(pxs8("\033z"));
    showSequenceFromString8(pxs8("\033[1;5D"));
    showSequenceFromString8(pxs8("\033[A"));
    showSequenceFromString8(pxs8("\033[38;2;1;2;3m"));
    showSequenceFromString8(pxs8("\033[9m"));
}
