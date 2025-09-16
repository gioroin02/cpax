#ifndef PX_LINUX_CONSOLE_MESSAGE_H
#define PX_LINUX_CONSOLE_MESSAGE_H

#include "import.h"

PxConsoleMsg
pxLinuxConsoleReadMsg(PxReader* self, PxArena* arena);

PxConsoleMsg
pxLinuxConsolePollMsg(PxReader* self, PxArena* arena);

#endif // PX_LINUX_CONSOLE_MESSAGE_H
