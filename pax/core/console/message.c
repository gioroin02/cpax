#ifndef PX_CORE_CONSOLE_MESSAGE_C
#define PX_CORE_CONSOLE_MESSAGE_C

#include "message.h"

#if PX_SYSTEM == PX_SYSTEM_WINDOWS

    #include "../../windows/console/message.c"

    #define __pxConsoleReadMsg__ pxWindowsConsoleReadMsg
    #define __pxConsolePollMsg__ pxWindowsConsolePollMsg

#elif PX_SYSTEM == PX_SYSTEM_LINUX

    #include "../../linux/console/message.c"

    #define __pxConsoleReadMsg__ pxLinuxConsoleReadMsg
    #define __pxConsolePollMsg__ pxLinuxConsolePollMsg

#else

    #error "Unknown platform"

#endif

PxConsoleMsg
pxConsoleMsgKeybdPress(pxiword button, pxuword modifs, pxi32 unicode)
{
    return (PxConsoleMsg) {
        .type = PX_CONSOLE_MSG_KEYBD_PRESS,

        .keybd_press = {
            .button  = button,
            .modifs  = modifs,
            .unicode = unicode,
        },
    };
}

PxConsoleMsg
pxConsoleMsgKeybdRelease(pxiword button, pxuword modifs, pxi32 unicode)
{
    return (PxConsoleMsg) {
        .type = PX_CONSOLE_MSG_KEYBD_RELEASE,

        .keybd_release = {
            .button  = button,
            .modifs  = modifs,
            .unicode = unicode,
        },
    };
}

PxConsoleMsg
pxConsoleReadMsg(PxReader self, PxArena* arena)
{
    return __pxConsoleReadMsg__(self, arena);
}

PxConsoleMsg
pxConsolePollMsg(PxReader self, PxArena* arena)
{
    return __pxConsolePollMsg__(self, arena);
}

#endif // PX_CORE_CONSOLE_MESSAGE_C
