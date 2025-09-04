#ifndef PX_CONSOLE_CONSOLE_H
#define PX_CONSOLE_CONSOLE_H

#include "mode.h"

typedef void* PxConsole;

PxConsole
pxConsoleCreate(PxArena* arena);

pxb8
pxConsoleSetMode(PxConsole self, PxConsoleMode mode);

pxb8
pxConsoleSetModeDefault(PxConsole self);

pxb8
pxConsoleSetModeRaw(PxConsole self);

pxiword
pxConsoleWriteMemory(PxConsole self, void* memory, pxiword amount, pxiword stride);

pxiword
pxConsoleReadMemory(PxConsole self, void* memory, pxiword amount, pxiword stride);

#endif // PX_CONSOLE_CONSOLE_H
