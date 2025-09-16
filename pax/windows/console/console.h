#ifndef PX_WINDOWS_CONSOLE_CONSOLE_H
#define PX_WINDOWS_CONSOLE_CONSOLE_H

#include "import.h"

typedef struct PxWindowsConsole PxWindowsConsole;

PxWindowsConsole*
pxWindowsConsoleCreate(PxArena* arena);

pxb8
pxWindowsConsoleModeDefault(PxWindowsConsole* self);

pxb8
pxWindowsConsoleModeMessage(PxWindowsConsole* self);

pxiword
pxWindowsConsoleWriteMemory8(PxWindowsConsole* self, pxu8* memory, pxiword length);

pxiword
pxWindowsConsoleReadMemory8(PxWindowsConsole* self, pxu8* memory, pxiword length);

#endif // PX_WINDOWS_CONSOLE_CONSOLE_H
