#include "../export.h"

#include <stdio.h>

int
main(int argc, char** argv)
{
    pxu8 memory[256] = {0};

    pxiword wrote = pxMemory8WriteUnsigned(memory, 256, 16,
        PX_FORMAT_RADIX_16, PX_FORMAT_FLAG_UPPER | PX_FORMAT_FLAG_PLUS);

    pxuword value = 0;

    pxiword read = pxMemory8ReadUnsigned(memory, wrote, &value,
        PX_FORMAT_RADIX_16, PX_FORMAT_FLAG_UPPER | PX_FORMAT_FLAG_PLUS);

    printf("'%.*s' [%lli], %llu, %lli, %s\n", pxas(int, wrote), memory, wrote,
        value, read, read == wrote ? "ok" : "ko");
}
