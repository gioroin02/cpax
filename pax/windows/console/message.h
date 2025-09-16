#ifndef PX_WINDOWS_CONSOLE_MESSAGE_H
#define PX_WINDOWS_CONSOLE_MESSAGE_H

#include "import.h"

PxConsoleMsg
pxWindowsConsoleReadMsg(PxInput* self, PxArena* arena);

PxConsoleMsg
pxWindowsConsolePollMsg(PxInput* self, PxArena* arena);

#endif // PX_WINDOWS_CONSOLE_MESSAGE_H
