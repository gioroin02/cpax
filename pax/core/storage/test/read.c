#include "../export.h"

#include <stdio.h>

int
main(int argc, char** argv)
{
    PxArena arena = pxMemoryReserve(16);

    PxString8 base = pxs8("");
    PxString8 name = pxString8FromMemory(argv[0], 128);

    PxFile file = pxFileOpen(&arena,
        base, name, PX_FILE_MODE_READ);

    if (file != 0)
        printf("%p\n", file);

    pxFileClose(file);
}
