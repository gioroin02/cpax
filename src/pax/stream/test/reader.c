#include "../export.h"

#include <stdio.h>

void
readBytePerByte(PxReader* reader)
{
    pxword8 word = pxReaderPeek(reader, 0);

    while (word != 0) {
        printf("%3u", word);

        if (pxUnicodeIsAscii(word) != 0)
            printf(" (%c)", word);

        printf("\n");

        word = pxReaderDrop(reader, 1);
    }
}

int
main(int argc, char** argv)
{
    pxword8 memory[PX_MEMORY_KIB] = {0};

    PxArena arena = pxArenaMake(memory, pxSize(memory));

    PxBuffer8 source = pxBuffer8Reserve(&arena, 256);
    PxBuffer8 buffer = pxBuffer8Reserve(&arena, 256);

    PxReader reader = pxReaderFromBuffer(&source, &buffer);

    pxBuffer8WriteMemoryTail(&source, pxCast(pxword8*, "ciao"), 4);

    readBytePerByte(&reader);

    pxBuffer8WriteMemoryTail(&source, pxCast(pxword8*, "ciao"), 4);

    PxString8 line = pxReaderLine(&reader, &arena, 16);

    printf("%.*s\n", pxCast(int, line.length),
        line.memory);
}
