#include "../export.h"

#include <stdio.h>

void
pxConsoleClear(PxConsole self)
{
    pxConsoleWriteMemory(self, "\033[0m\033c", 6, 1);
}

void
pxConsolePaint(PxConsole self, pxu8 symbol, pxu8 x, pxu8 y, pxu8 color)
{
    fprintf(stdout, "\033[%u;%uH", y, x);
    fprintf(stdout, "\033[38;5;%um", color);

    fprintf(stdout, "%c", symbol);

    fflush(stdout);
}

void
pxConsoleShowCursor(PxConsole self, pxb8 state)
{
    switch (state) {
        case 0:
            pxConsoleWriteMemory(self, "\033[?25l", 6, 1);
        break;

        default:
            pxConsoleWriteMemory(self, "\033[?25h", 6, 1);
        break;
    }
}

int
main(int argc, char** argv)
{
    PxArena arena = pxMemoryReserve(16);

    PxConsole console = pxConsoleCreate(&arena, PX_MEMORY_KIB);

    pxConsoleInputModeRaw(console);

    pxu8 x     = 1;
    pxu8 y     = 1;
    pxu8 color = 0;

    pxConsoleClear(console);
    pxConsoleShowCursor(console, 0);

    while (1) {
        PxConsoleEvent event = pxConsoleReadEvent(console);

        if (event.type == PX_CONSOLE_EVENT_KEYBD_PRESS) {
            if (event.keybd_press.button == PX_CONSOLE_KEYBD_ESCAPE)
                break;

            if (event.keybd_press.button == PX_CONSOLE_KEYBD_ARROW_LEFT)
                x -= 1;

            if (event.keybd_press.button == PX_CONSOLE_KEYBD_ARROW_RIGHT)
                x += 1;

            if (event.keybd_press.button == PX_CONSOLE_KEYBD_ARROW_UP)
                y -= 1;

            if (event.keybd_press.button == PX_CONSOLE_KEYBD_ARROW_DOWN)
                y += 1;

            x = pxClamp(x, 1, 25);
            y = pxClamp(y, 1, 25);

            pxConsolePaint(console, '@', x, y, color);
        }

        color = (color + 1) % 256;
    }

    pxConsoleClear(console);

    pxConsoleInputModeRestore(console);
}
