#include "../export.h"

#include <stdio.h>

int
main(int argc, char** argv)
{
    PxArena arena = pxMemoryReserve(16);

    PxConsole console = pxConsoleCreate(&arena);

    pxConsoleSetMode(console, PX_CONSOLE_MODE_RAW);

    pxu8 byte = 0;

    while (1) {
        pxConsoleReadMemory(console, &byte, 1, 1);

        if (byte == PX_ASCII_LOWER_Q)
            break;
    }

    pxConsoleSetMode(console, PX_CONSOLE_MODE_DEFAULT);
}
