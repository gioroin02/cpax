#include "../export.h"
#include "../../memory/export.h"

#include <stdio.h>

int
main(int argc, char** argv)
{
    PxArena   arena  = pxMemoryReserve(32);
    PxBuffer8 buffer = pxBuffer8Reserve(&arena, 256);
    PxOutput  writer = pxBufferWriter(&buffer, &arena, 256);

    PxString8 string = {0};
    pxiword   size   = 0;

    size = pxWriterFormatList(&writer, &arena, 0, 5, (PxFormatCmd[]) {
        pxFormatCmdString8(pxs8("coords = {x = ")),
        pxFormatCmdInteger(PX_IWORD_MAX, PX_FORMAT_RADIX_10, PX_FORMAT_FLAG_PLUS),
        pxFormatCmdString8(pxs8(", y = ")),
        pxFormatCmdInteger(PX_IWORD_MIN, PX_FORMAT_RADIX_10, PX_FORMAT_FLAG_NONE),
        pxFormatCmdString8(pxs8(", z = ${?}}")),
    });

    pxWriterFlush(&writer);

    string = pxBuffer8ReadString8Head(&buffer, &arena, buffer.size);

    printf("'\x1b[34m%s\x1b[0m' (%lli)\n", string.memory, size);

    size = pxWriterFormatVargs(&writer, &arena, "coords = {x = ${0}, y = ${1}, z = ${2}}",
        pxFormatCmdInteger(PX_IWORD_MAX, PX_FORMAT_RADIX_10, PX_FORMAT_FLAG_PLUS),
        pxFormatCmdInteger(PX_IWORD_MIN, PX_FORMAT_RADIX_10, PX_FORMAT_FLAG_NONE));

    pxWriterFlush(&writer);

    string = pxBuffer8ReadString8Head(&buffer, &arena, buffer.size);

    printf("'\x1b[34m%s\x1b[0m' (%lli)\n", string.memory, size);

    size = pxWriterFormatVargs(&writer, &arena, "coords = {x = 0, y = 1, z = 2}", {0});

    pxWriterFlush(&writer);

    string = pxBuffer8ReadString8Head(&buffer, &arena, buffer.size);

    printf("'\x1b[34m%s\x1b[0m' (%lli)\n", string.memory, size);
}
