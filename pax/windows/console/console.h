#ifndef PX_WINDOWS_CONSOLE_CONSOLE_H
#define PX_WINDOWS_CONSOLE_CONSOLE_H

#include "import.h"

typedef struct PxWindowsConsole PxWindowsConsole;

PxWindowsConsole*
pxWindowsConsoleCreate(PxArena* arena);

pxb8
pxWindowsConsoleSetModeDefault(PxWindowsConsole* self);

pxb8
pxWindowsConsoleSetModeRaw(PxWindowsConsole* self);

pxiword
pxWindowsConsoleWrite(PxWindowsConsole* self, PxBuffer8* buffer);

pxiword
pxWindowsConsoleWriteMemory(PxWindowsConsole* self, void* memory, pxiword amount, pxiword stride);

pxiword
pxWindowsConsoleRead(PxWindowsConsole* self, PxBuffer8* buffer);

pxiword
pxWindowsConsoleReadMemory(PxWindowsConsole* self, void* memory, pxiword amount, pxiword stride);

PxConsoleEvent
pxWindowsConsoleReadEvent(PxWindowsConsole* self, PxBuffer8* buffer);

#endif // PX_WINDOWS_CONSOLE_CONSOLE_H
