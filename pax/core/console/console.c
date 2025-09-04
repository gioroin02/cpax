#ifndef PX_CONSOLE_CONSOLE_C
#define PX_CONSOLE_CONSOLE_C

#include "console.h"

#if PX_SYSTEM == PX_SYSTEM_WINDOWS

    #include "../../windows/console/console.c"

    #define __pxConsoleCreate__         pxWindowsConsoleCreate
    #define __pxConsoleSetModeDefault__ pxWindowsConsoleSetModeDefault
    #define __pxConsoleSetModeRaw__     pxWindowsConsoleSetModeRaw
    #define __pxConsoleReadMemory__     pxWindowsConsoleReadMemory

#elif PX_SYSTEM == PX_SYSTEM_LINUX

    #include "../../linux/console/console.c"

    #define __pxConsoleCreate__         pxLinuxConsoleCreate
    #define __pxConsoleSetModeDefault__ pxLinuxConsoleSetModeDefault
    #define __pxConsoleSetModeRaw__     pxLinuxConsoleSetModeRaw
    #define __pxConsoleReadMemory__     pxLinuxConsoleReadMemory

#else

    #error "Unknown platform"

#endif

PxConsole
pxConsoleCreate(PxArena* arena)
{
    return __pxConsoleCreate__(arena);
}

pxb8
pxConsoleSetMode(PxConsole self, PxConsoleMode mode)
{
    switch (mode) {
        case PX_CONSOLE_MODE_DEFAULT:
            return pxConsoleSetModeDefault(self);

        case PX_CONSOLE_MODE_RAW:
            return pxConsoleSetModeRaw(self);

        default: break;
    }

    return 0;
}

pxb8
pxConsoleSetModeDefault(PxConsole self)
{
    return __pxConsoleSetModeDefault__(self);
}

pxb8
pxConsoleSetModeRaw(PxConsole self)
{
    return __pxConsoleSetModeRaw__(self);
}

pxiword
pxConsoleReadMemory(PxConsole self, void* memory, pxiword amount, pxiword stride)
{
    return __pxConsoleReadMemory__(self, memory, amount, stride);
}

#endif // PX_CONSOLE_CONSOLE_C
