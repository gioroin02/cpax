#ifndef PX_CORE_CONSOLE_CONSOLE_H
#define PX_CORE_CONSOLE_CONSOLE_H

#include "command.h"
#include "message.h"

typedef void* PxConsole;

typedef enum PxConsoleMode
{
    PX_CONSOLE_MODE_NONE,
    PX_CONSOLE_MODE_DEFAULT,
    PX_CONSOLE_MODE_MESSAGE,
}
PxConsoleMode;

PxConsole
pxConsoleCreate(PxArena* arena);

pxb8
pxConsoleSetMode(PxConsole self, PxConsoleMode mode);

pxiword
pxConsoleWriteMemory8(PxConsole self, pxu8* memory, pxiword length);

pxiword
pxConsoleReadMemory8(PxConsole self, pxu8* memory, pxiword length);

PxReader
pxReaderFromConsole(PxConsole self);

PxWriter
pxWriterFromConsole(PxConsole self);

#endif // PX_CORE_CONSOLE_CONSOLE_H
