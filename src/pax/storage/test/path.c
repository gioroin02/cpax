#include "../export.h"

#include <stdio.h>

int
main(int argc, char** argv)
{
    PxArena arena = pxMemoryReserve(16);

    PxPath path = pxPathFromString8(&arena,
        pxString8FromMemory(argv[0], 1024), pxs8("\\"));

    for (PxStringListNode* n = path.items.head; n != 0; n = n->next) {
        for (pxiword i = 0; i < n->length; i += 1)
            printf("%c", pxCast(pxi8, n->memory[i]));

        if (n->next != 0)
            printf(" - ");
    }
    printf("\n");

    PxString8 string = pxString8FromPath(&arena,
        &path, pxs8("/"));

    printf("%s\n", string.memory);
}
