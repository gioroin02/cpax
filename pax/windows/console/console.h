#ifndef PX_WINDOWS_CONSOLE_CONSOLE_H
#define PX_WINDOWS_CONSOLE_CONSOLE_H

#include "import.h"

typedef struct PxWindowsConsole PxWindowsConsole;

PxWindowsConsole*
pxWindowsConsoleCreate(PxArena* arena);

pxb8
pxWindowsConsoleKeybdModeRaw(PxWindowsConsole* self);

pxb8
pxWindowsConsoleKeybdModeRestore(PxWindowsConsole* self);

pxiword
pxWindowsConsoleWriteMemory(PxWindowsConsole* self, void* memory, pxiword amount, pxiword stride);

pxiword
pxWindowsConsoleReadMemory(PxWindowsConsole* self, void* memory, pxiword amount, pxiword stride);

PxConsoleEvent
pxWindowsConsoleReadEvent(PxWindowsConsole* self, PxArena* arena);

#endif // PX_WINDOWS_CONSOLE_CONSOLE_H
