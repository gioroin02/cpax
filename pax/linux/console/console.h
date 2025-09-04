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
pxLinuxConsoleReadMemory(PxLinuxConsole* self, void* memory, pxiword amount, pxiword stride);

#endif // PX_LINUX_CONSOLE_CONSOLE_H
