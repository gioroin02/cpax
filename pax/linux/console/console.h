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
pxLinuxConsoleWrite(PxLinuxConsole* self, PxBuffer8* buffer);

pxiword
pxLinuxConsoleWriteMemory(PxLinuxConsole* self, void* memory, pxiword amount, pxiword stride);

pxiword
pxLinuxConsoleRead(PxLinuxConsole* self, PxBuffer8* buffer);

pxiword
pxLinuxConsoleReadMemory(PxLinuxConsole* self, void* memory, pxiword amount, pxiword stride);

PxConsoleEvent
pxLinuxConsoleReadEvent(PxLinuxConsole* self, PxBuffer8* buffer);

#endif // PX_LINUX_CONSOLE_CONSOLE_H
