#ifndef PX_CORE_CONSOLE_EVENT_C
#define PX_CORE_CONSOLE_EVENT_C

#include "event.h"

PxConsoleEvent
pxConsoleEventKeybdPress(pxiword button, pxuword modifs, pxi32 unicode)
{
    return (PxConsoleEvent) {
        .type = PX_CONSOLE_EVENT_KEYBD_PRESS,
        .keybd_press = {
            .button  = button,
            .modifs  = modifs,
            .unicode = unicode,
        },
    };
}

PxConsoleEvent
pxConsoleEventKeybdRelease(pxiword button, pxuword modifs, pxi32 unicode)
{
    return (PxConsoleEvent) {
        .type = PX_CONSOLE_EVENT_KEYBD_RELEASE,
        .keybd_press = {
            .button  = button,
            .modifs  = modifs,
            .unicode = unicode,
        },
    };
}

#endif // PX_CORE_CONSOLE_EVENT_C
