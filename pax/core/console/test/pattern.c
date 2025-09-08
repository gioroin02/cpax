#include "../export.h"

#include <stdio.h>

void
paintAt(pxu8 symbol, pxu8 x, pxu8 y, pxu8 r, pxu8 g, pxu8 b)
{
    fprintf(stdout, "\033[%u;%uH\033[38;2;%u;%u;%um%c",
        x - 1, y, r, g, b, symbol);
}

void
clear()
{
    fprintf(stdout, "\033[0m\033[2J");
}

void
flush()
{
    fflush(stdout);
}

int
main(int argc, char** argv)
{
    PxArena arena = pxMemoryReserve(16);

    PxConsole console = pxConsoleCreate(&arena, PX_MEMORY_KIB);

    pxConsoleInputModeRaw(console);

    pxu8 r = 0;
    pxu8 g = 0;
    pxu8 b = 0;

    clear();

    while (1) {
        PxConsoleEvent event = pxConsoleReadEvent(console);

        if (event.type == PX_CONSOLE_EVENT_KEYBD_PRESS) {
            if (event.keybd_press.button == PX_CONSOLE_KEYBD_ESCAPE)
                break;
        }

        paintAt('@', 5, 5, r, g, b);
        flush();

        r = (r + 1) % 128 + 128;
        g = (g + 1) % 128 + 128;
        b = (b + 1) % 128 + 128;

        clear();
        flush();
    }

    clear();

    pxConsoleInputModeRestore(console);
}
