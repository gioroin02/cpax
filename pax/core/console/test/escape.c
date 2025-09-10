#include "../export.h"

#include <stdio.h>

void
showEscapeFromString8(PxString8 string)
{
    PxEscape escape = {0};
    pxiword  size   = 0;

    pxb8 state = pxEscapeFromString8(&escape, string, &size);

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

    printf("'\x1b[0m -> %s\n", state != 0 ? "\x1b[32mT\x1b[0m" : "\x1b[31mF\x1b[0m");

    if (state != 0) {
        printf(" -> type = %u\n", escape.type);

        for (pxiword i = 0; i < escape.size; i += 1)
            printf(" -> item = %llu\n", escape.items[i]);
    }
}

int
main(int argc, char** argv)
{
    printf("VALID:\n\n");

    showEscapeFromString8(pxs8("\033[1;5D"));
    showEscapeFromString8(pxs8("\033[A"));
    showEscapeFromString8(pxs8("\033[38;2;1;2;3m"));
    showEscapeFromString8(pxs8("\033[9m"));
    showEscapeFromString8(pxs8("\033[97u"));

    printf("\nINVALID:\n\n");

    showEscapeFromString8(pxs8("\033[\0331;6A"));
    showEscapeFromString8(pxs8("\033z"));
}
