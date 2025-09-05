#ifndef PX_LINUX_CONSOLE_CONSOLE_H
#define PX_LINUX_CONSOLE_CONSOLE_H

#include "import.h"

typedef struct PxLinuxConsole PxLinuxConsole;

PxLinuxConsole*
pxLinuxConsoleCreate(PxArena* arena);

pxb8
pxLinuxConsoleSetModeDefault(PxLinuxConsole* self);

pxb8
pxLinuxConsoleSetModeRaw(PxLinuxConsole* self);

pxiword
pxLinuxConsoleWriteMemory(PxLinuxConsole* self, void* memory, pxiword amount, pxiword stride);

pxiword
pxLinuxConsoleReadMemory(PxLinuxConsole* self, void* memory, pxiword amount, pxiword stride);

PxConsoleEvent
pxLinuxConsoleReadEvent(PxLinuxConsole* self, PxArena* arena);

#endif // PX_LINUX_CONSOLE_CONSOLE_H
