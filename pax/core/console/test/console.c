#include "../export.h"

#include <stdio.h>

int
main(int argc, char** argv)
{
    PxArena arena = pxMemoryReserve(16);

    PxConsole console = pxConsoleCreate(&arena);
    PxBuffer8 buffer  = pxBuffer8Reserve(&arena, PX_MEMORY_KIB);

    pxConsoleSetMode(console, PX_CONSOLE_MODE_RAW);

    while (1) {
        PxConsoleEvent event = pxConsoleReadEvent(console, &buffer);

        if (event.type == PX_CONSOLE_EVENT_KEYBD_PRESS)
            printf("%li\r\n", event.keybd_press.unicode);

        if (event.type == PX_CONSOLE_EVENT_KEYBD_RELEASE) {
            printf("%li\r\n", event.keybd_release.unicode);

            if (event.keybd_release.button == PX_CONSOLE_KEYBD_ESCAPE)
                break;
        }
    }

    pxConsoleSetMode(console, PX_CONSOLE_MODE_DEFAULT);
}
