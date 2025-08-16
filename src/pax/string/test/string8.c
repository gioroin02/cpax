#include "../export.h"

#include <stdio.h>

int
main(int argc, char** argv)
{
    pxword8 memory[PX_MEMORY_KIB] = {0};

    PxArena arena = pxArenaMake(memory, pxSize(memory));

    PxString8 str = pxString8CopyMemory(&arena,
        pxCast(pxword8*, "ciao"), 4);

    printf("%.*s\n", pxCast(int, str.length), str.memory);
}
