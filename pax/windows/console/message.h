#ifndef PX_WINDOWS_CONSOLE_MESSAGE_H
#define PX_WINDOWS_CONSOLE_MESSAGE_H

#include "import.h"

PxConsoleMsg
pxWindowsConsoleReadMsg(PxReader* self, PxArena* arena);

PxConsoleMsg
pxWindowsConsolePollMsg(PxReader* self, PxArena* arena);

#endif // PX_WINDOWS_CONSOLE_MESSAGE_H
