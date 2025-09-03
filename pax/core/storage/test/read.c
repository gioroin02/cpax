#include "../export.h"

#include <stdio.h>

int
main(int argc, char** argv)
{
    PxArena arena = pxMemoryReserve(16);

    if (argc < 2) return 1;

    PxString8 base = pxs8(".");
    PxString8 name = pxString8FromMemory(argv[1], 128);

    PxFile file = pxFileOpen(&arena,
        base, name, PX_FILE_MODE_READ);

    if (file != 0)
        printf("%p\n", file);

    PxBuffer8 buffer = pxBuffer8Reserve(&arena, 256);

    while (1) {
        if (pxFileRead(file, &buffer) == 0)
            break;

        printf("%.*s", pxCast(int, buffer.size),
            buffer.memory);

        pxBuffer8Clear(&buffer);
    }

    pxFileClose(file);
}
