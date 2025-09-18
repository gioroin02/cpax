#include "../export.h"
#include "../../memory/export.h"

#include <stdio.h>

int
main(int argc, char** argv)
{
    PxArena   arena  = pxMemoryReserve(32);
    PxBuffer8 buffer = pxBuffer8Reserve(&arena, 256);

    PxString8 string = {0};
    pxiword   size   = 0;

    size = pxBuffer8PrintList(&buffer, (PxPrintCmd[]) {
        pxPrintCmdString8(pxs8("coords = {x = ")),
        pxPrintCmdInteger(PX_IWORD_MAX),
        pxPrintCmdString8(pxs8(", y = ")),
        pxPrintCmdInteger(PX_IWORD_MIN),
        pxPrintCmdString8(pxs8(", z = ${?}}")),
    }, 5);

    string = pxBuffer8ReadString8Head(&buffer, &arena, buffer.size);

    printf("'\x1b[34m%s\x1b[0m' (%lli)\n", string.memory, size);

    size = pxBuffer8PrintVargs(&buffer, "coords = {x = ${0}, y = ${1}, z = ${-1}}",
        pxPrintCmdInteger(PX_IWORD_MAX), pxPrintCmdInteger(PX_IWORD_MIN));

    string = pxBuffer8ReadString8Head(&buffer, &arena, buffer.size);

    printf("'\x1b[34m%s\x1b[0m' (%lli)\n", string.memory, size);

    size = pxBuffer8PrintVargs(&buffer, "coords = {x = 0, y = 1, z = 2}", {0});

    string = pxBuffer8ReadString8Head(&buffer, &arena, buffer.size);

    printf("'\x1b[34m%s\x1b[0m' (%lli)\n", string.memory, size);
}
