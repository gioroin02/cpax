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
pxConsoleWrite(PxConsole self, PxBuffer8* buffer);

pxiword
pxConsoleWriteMemory(PxConsole self, void* memory, pxiword amount, pxiword stride);

pxiword
pxConsoleRead(PxConsole self, PxBuffer8* buffer);

pxiword
pxConsoleReadMemory(PxConsole self, void* memory, pxiword amount, pxiword stride);

PxWriter
pxConsoleWriter(PxConsole self, PxBuffer8* buffer);

PxReader
pxConsoleReader(PxConsole self, PxBuffer8* buffer);

#endif // PX_CONSOLE_CONSOLE_H
