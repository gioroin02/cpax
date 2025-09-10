#include "../export.h"

#include <stdio.h>

int
main(int argc, char** argv)
{
    PxArena   arena   = pxMemoryReserve(16);
    PxConsole console = pxConsoleCreate(&arena, PX_MEMORY_KIB);

    pxb8 active = 1;

    pxu8    buffer[PX_MEMORY_KB] = {0};
    pxiword length               = PX_MEMORY_KIB;

    pxConsoleSetMode(console, PX_CONSOLE_MODE_EVENT);

    pxConsoleWriteMemory(console, "\x1b[?u", 10, 1);

    pxiword size = pxConsoleReadMemory(console, buffer, length, 1);

    PxString8 string = {.memory = buffer, .length = size};

    string = pxString8TrimPrefix(string, pxs8("\x1b[?"));
    string = pxString8TrimSuffix(string, pxs8("u"));

    printf("%.*s\n", pxCast(int, string.length), string.memory);

    pxConsoleSetMode(console, PX_CONSOLE_MODE_DEFAULT);
}
