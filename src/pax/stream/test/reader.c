#include "../export.h"

#include <stdio.h>

int
main(int argc, char** argv)
{
    pxword8 memory[PX_MEMORY_KIB] = {0};

    PxArena arena = pxArenaMake(memory, pxSize(memory));

    PxBuffer8 source = pxBuffer8Reserve(&arena, 256);
    PxBuffer8 buffer = pxBuffer8Reserve(&arena, 256);

    pxBuffer8WriteMemoryTail(&source, pxCast(pxword8*, "ciao"), 4);

    PxReader reader = pxReaderFromBuffer8(&source);
    pxword8  word   = pxReaderPeek(reader, &buffer, 0);

    while (word != 0) {
        printf("%c\n", word);

        word = pxReaderMove(reader, &buffer, 1);
    }
}
