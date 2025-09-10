#include "../export.h"

#include <stdio.h>

int
main(int argc, char** argv)
{
    PxArena arena = pxMemoryReserve(16);

    PxConsole console = pxConsoleCreate(&arena, PX_MEMORY_KIB);

    pxConsoleSetMode(console, PX_CONSOLE_MODE_ENHANCED);

    while (1) {
        PxConsoleEvent event = pxConsoleReadEvent(console);

        if (event.type == PX_CONSOLE_EVENT_KEYBD_PRESS) {
            printf("btn = %lli, mod = %llu, uni = %li\r\n",
                event.keybd_press.button,
                event.keybd_press.modifs,
                event.keybd_press.unicode
            );
        }

        if (event.type == PX_CONSOLE_EVENT_KEYBD_RELEASE) {
            printf("btn = %lli, mod = %llu, uni = %li\r\n",
                event.keybd_release.button,
                event.keybd_release.modifs,
                event.keybd_release.unicode
            );

            if (event.keybd_release.button == PX_CONSOLE_KEYBD_ESCAPE)
                break;
        }
    }

    pxConsoleSetMode(console, PX_CONSOLE_MODE_BUFFERED);
}
