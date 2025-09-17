#include "../export.h"

#include <stdio.h>

void
readBytePerByte(PxReader reader)
{
    pxu8 byte = 0;

    while (pxReadByte(reader, &byte) != 0) {
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
    PxReader  reader = pxReaderFromBuffer8(&source);

    pxBuffer8WriteString8Tail(&source, pxs8("ciao\narrivederci"));

    readBytePerByte(reader);

    pxBuffer8WriteString8Tail(&source, pxs8("ciao\narrivederci"));

    PxString8 string = pxReadString8(reader, &arena, 16);

    printf("[%.*s]\n", pxas(int, string.length),
        string.memory);
}
