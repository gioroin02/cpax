#ifndef PX_CORE_CONSOLE_CONSOLE_H
#define PX_CORE_CONSOLE_CONSOLE_H

#include "event.h"

typedef void* PxConsole;

PxConsole
pxConsoleCreate(PxArena* arena, pxiword length);

pxb8
pxConsoleInputModeRaw(PxConsole self);

pxb8
pxConsoleInputModeRestore(PxConsole self);

pxiword
pxConsoleWrite(PxConsole self, PxBuffer8* buffer);

pxiword
pxConsoleWriteMemory(PxConsole self, void* memory, pxiword amount, pxiword stride);

pxiword
pxConsoleRead(PxConsole self, PxBuffer8* buffer);

pxiword
pxConsoleReadMemory(PxConsole self, void* memory, pxiword amount, pxiword stride);

PxConsoleEvent
pxConsoleReadEvent(PxConsole self);

PxWriter
pxConsoleWriter(PxConsole self, PxArena* arena, pxiword length);

PxReader
pxConsoleReader(PxConsole self, PxArena* arena, pxiword length);

#endif // PX_CORE_CONSOLE_CONSOLE_H
