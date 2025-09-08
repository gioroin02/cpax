#ifndef PX_LINUX_CONSOLE_CONSOLE_H
#define PX_LINUX_CONSOLE_CONSOLE_H

#include "import.h"

typedef struct PxLinuxConsole PxLinuxConsole;

PxLinuxConsole*
pxLinuxConsoleCreate(PxArena* arena, pxiword length);

pxb8
pxLinuxConsoleInputModeRaw(PxLinuxConsole* self);

pxb8
pxLinuxConsoleInputModeRestore(PxLinuxConsole* self);

pxiword
pxLinuxConsoleWriteMemory(PxLinuxConsole* self, void* memory, pxiword amount, pxiword stride);

pxiword
pxLinuxConsoleReadMemory(PxLinuxConsole* self, void* memory, pxiword amount, pxiword stride);

PxConsoleEvent
pxLinuxConsoleReadEvent(PxLinuxConsole* self);

#endif // PX_LINUX_CONSOLE_CONSOLE_H
