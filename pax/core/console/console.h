#ifndef PX_CORE_CONSOLE_CONSOLE_H
#define PX_CORE_CONSOLE_CONSOLE_H

#include "event.h"

typedef void* PxConsole;

PxConsole
pxConsoleCreate(PxArena* arena);

pxb8
pxConsoleKeybdModeRaw(PxConsole self);

pxb8
pxConsoleKeybdModeRestore(PxConsole self);

pxiword
pxConsoleWrite(PxConsole self, PxBuffer8* buffer);

pxiword
pxConsoleWriteMemory(PxConsole self, void* memory, pxiword amount, pxiword stride);

pxiword
pxConsoleRead(PxConsole self, PxBuffer8* buffer);

pxiword
pxConsoleReadMemory(PxConsole self, void* memory, pxiword amount, pxiword stride);

PxConsoleEvent
pxConsoleReadEvent(PxConsole self, PxArena* arena);

PxWriter
pxConsoleWriter(PxConsole self, PxBuffer8* buffer);

PxReader
pxConsoleReader(PxConsole self, PxBuffer8* buffer);

#endif // PX_CORE_CONSOLE_CONSOLE_H
