#ifndef PX_CONSOLE_CONSOLE_C
#define PX_CONSOLE_CONSOLE_C

#include "console.h"

#if PX_SYSTEM == PX_SYSTEM_WINDOWS

    #include "../../windows/console/console.c"

    #define __pxConsoleCreate__         pxWindowsConsoleCreate
    #define __pxConsoleSetModeDefault__ pxWindowsConsoleSetModeDefault
    #define __pxConsoleSetModeRaw__     pxWindowsConsoleSetModeRaw
    #define __pxConsoleWriteMemory__    pxWindowsConsoleWriteMemory
    #define __pxConsoleReadMemory__     pxWindowsConsoleReadMemory
    #define __pxConsoleNext__           pxWindowsConsoleNext

#elif PX_SYSTEM == PX_SYSTEM_LINUX

    #include "../../linux/console/console.c"

    #define __pxConsoleCreate__         pxLinuxConsoleCreate
    #define __pxConsoleSetModeDefault__ pxLinuxConsoleSetModeDefault
    #define __pxConsoleSetModeRaw__     pxLinuxConsoleSetModeRaw
    #define __pxConsoleWriteMemory__    pxLinuxConsoleWriteMemory
    #define __pxConsoleReadMemory__     pxLinuxConsoleReadMemory
    #define __pxConsoleNext__           pxLinuxConsoleNext

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
pxConsoleWrite(PxConsole self, PxBuffer8* buffer)
{
    pxBuffer8Normalize(buffer);

    pxu8*   memory = buffer->memory;
    pxiword size   = buffer->size;

    if (size <= 0) return 0;

    pxiword temp = pxConsoleWriteMemory(self, memory, size, 1);

    buffer->size -= temp;
    buffer->head  = (buffer->head + temp) % buffer->length;

    return temp;
}

pxiword
pxConsoleWriteMemory(PxConsole self, void* memory, pxiword amount, pxiword stride)
{
    return __pxConsoleWriteMemory__(self, memory, amount, stride);
}

pxiword
pxConsoleRead(PxConsole self, PxBuffer8* buffer)
{
    pxBuffer8Normalize(buffer);

    pxu8*   memory = buffer->memory + buffer->size;
    pxiword size   = buffer->length - buffer->size;

    if (size <= 0) return 0;

    pxiword temp = pxConsoleReadMemory(self, memory, size, 1);

    buffer->size += temp;
    buffer->tail  = (buffer->tail + temp) % buffer->length;

    return temp;
}

pxiword
pxConsoleReadMemory(PxConsole self, void* memory, pxiword amount, pxiword stride)
{
    return __pxConsoleReadMemory__(self, memory, amount, stride);
}

PxConsoleEvent
pxConsoleNext(PxConsole self, PxArena* arena)
{
    return __pxConsoleNext__(self, arena);
}

PxWriter
pxConsoleWriter(PxConsole self, PxBuffer8* buffer)
{
    if (self == 0 || buffer == 0)
        return (PxWriter) {0};

    return (PxWriter) {
        .buffer = buffer,
        .ctxt   = self,
        .proc   = &pxConsoleWrite,
    };
}

PxReader
pxConsoleReader(PxConsole self, PxBuffer8* buffer)
{
    if (self == 0 || buffer == 0)
        return (PxReader) {0};

    return (PxReader) {
        .buffer = buffer,
        .ctxt   = self,
        .proc   = &pxConsoleRead,
    };
}

#endif // PX_CONSOLE_CONSOLE_C
