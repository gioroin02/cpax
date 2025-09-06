#include "../export.h"

#include <stdio.h>

int
main(int argc, char** argv)
{
    PxArena arena = pxMemoryReserve(16);

    PxConsole console = pxConsoleCreate(&arena);
    PxBuffer8 buffer  = pxBuffer8Reserve(&arena, PX_MEMORY_KIB);

    pxConsoleKeybdModeRaw(console);

    while (1) {
        PxConsoleEvent event = pxConsoleReadEvent(console, &arena);

        if (event.type == PX_CONSOLE_EVENT_KEYBD_PRESS) {
            printf("%lli, %llu, %li\r\n",
                event.keybd_press.button,
                event.keybd_press.modifs,
                event.keybd_press.unicode
            );
        }

        if (event.type == PX_CONSOLE_EVENT_KEYBD_RELEASE) {
            printf("%lli, %llu, %li\r\n",
                event.keybd_release.button,
                event.keybd_release.modifs,
                event.keybd_release.unicode
            );

            if (event.keybd_release.button == PX_CONSOLE_KEYBD_ESCAPE)
                break;
        }
    }

    pxConsoleKeybdModeRestore(console);
}
