#include "../export.h"

#include <stdio.h>

void
readBytePerByte(PxReader* reader)
{
    pxu8 byte = pxReaderPeekByte(reader, 0);

    while (byte != 0) {
        printf("%3u", byte);

        if (byte > 0x20 && byte < 0x80)
            printf(" (%c)", byte);

        printf("\n");

        byte = pxReaderNextByte(reader, 1);
    }
}

int
main(int argc, char** argv)
{
    pxu8 memory[PX_MEMORY_KIB] = {0};

    PxArena arena = pxArenaMake(memory, pxsize(memory));

    PxBuffer8 source = pxBuffer8Reserve(&arena, 256);
    PxReader  reader = pxReaderFromInput(pxInputFromBuffer8(&source), &arena, 4);

    pxBuffer8WriteString8Tail(&source, pxs8("ciao\narrivederci"));

    readBytePerByte(&reader);

    pxBuffer8WriteString8Tail(&source, pxs8("ciao\narrivederci"));

    PxString8 string = pxReaderNextString8Line(&reader, &arena, 16, 0);

    printf("[%.*s]\n", pxas(int, string.length),
        string.memory);
}
