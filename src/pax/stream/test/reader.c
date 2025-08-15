#include "../export.h"

#include <stdio.h>

int
main(int argc, char** argv)
{
    pxn8 memory[PX_MEMORY_KIB] = {0};

    PxArena arena = pxArenaMake(memory, px_size(memory));

    PxBuffer8 source = pxBuffer8Reserve(&arena, 256);
    PxBuffer8 buffer = pxBuffer8Reserve(&arena, 256);

    pxBuffer8WriteMemory8Tail(&source, px_as(pxn8*, "ciao"), 4);

    PxReader reader = pxReaderFromBuffer8(&source);
    pxn8     byte   = pxReaderPeek(reader, &buffer, 0);

    while (byte != 0) {
        printf("%c\n", byte);

        byte = pxReaderMove(reader, &buffer, 1);
    }
}
