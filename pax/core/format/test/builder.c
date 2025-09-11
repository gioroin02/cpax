#include "../export.h"
#include "../../memory/export.h"

#include <stdio.h>

int
main(int argc, char** argv)
{
    PxArena   arena   = pxMemoryReserve(32);
    PxBuilder builder = pxBuilderReserve(&arena, PX_MEMORY_KIB);

    PxString8 string = {0};

    pxBuilderList(&builder, 0, 5, (PxBuilderCmd[]) {
        pxBuilderCmdString8(pxs8("coords = {x = ")),
        pxBuilderCmdInteger(10, PX_FORMAT_OPTION_NONE, PX_IWORD_MAX),
        pxBuilderCmdString8(pxs8(", y = ")),
        pxBuilderCmdInteger(10, PX_FORMAT_OPTION_NONE, PX_IWORD_MIN),
        pxBuilderCmdString8(pxs8(", z = ${?}}")),
    });

    string = pxString8FromBuilder(&arena, &builder);

    printf("'\x1b[34m%s\x1b[0m'\n", string.memory);

    pxBuilderClear(&builder);

    PxString8 format = pxs8("coords = {x = ${0}, y = ${1}, z = ${2}}");

    pxBuilderFormat(&builder, format, 0, 2, (PxBuilderCmd[]) {
        pxBuilderCmdInteger(10, PX_FORMAT_OPTION_NONE, PX_IWORD_MAX),
        pxBuilderCmdInteger(10, PX_FORMAT_OPTION_NONE, PX_IWORD_MIN),
    });

    string = pxString8FromBuilder(&arena, &builder);

    printf("'\x1b[34m%s\x1b[0m'\n", string.memory);
}
