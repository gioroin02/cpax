#include "../export.h"

#include <stdio.h>

void
readBytePerByte(PxInput* input)
{
    pxu8 byte = 0;

    while (pxReadByte(input, &byte) != 0) {
        if (byte == 0) break;

        printf("%3u", byte);

        if (pxUnicodeIsAscii(byte) != 0)
            printf(" (%c)", byte);

        printf("\n");
    }
}

int
main(int argc, char** argv)
{
    pxu8 memory[PX_MEMORY_KIB] = {0};

    PxArena arena = pxArenaMake(memory, pxsize(memory));

    PxBuffer8 source = pxBuffer8Reserve(&arena, 256);
    PxInput   input = pxInputFromBuffer(&source);

    pxBuffer8WriteString8Tail(&source, pxs8("ciao\narrivederci"));

    readBytePerByte(&input);

    pxBuffer8WriteString8Tail(&source, pxs8("ciao\narrivederci"));

    PxString8 string = pxReadString8(&input, &arena, 16);

    printf("[%.*s]\n", pxas(int, string.length),
        string.memory);
}
