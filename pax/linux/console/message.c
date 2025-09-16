#ifndef PX_LINUX_CONSOLE_MESSAGE_C
#define PX_LINUX_CONSOLE_MESSAGE_C

#include "message.h"

PxConsoleMsg
pxLinuxConsoleReadMsg(PxReader* self, PxArena* arena)
{
    return (PxConsoleMsg) {.type = PX_CONSOLE_MSG_NONE};
}

PxConsoleMsg
pxLinuxConsolePollMsg(PxReader* self, PxArena* arena)
{
    return (PxConsoleMsg) {.type = PX_CONSOLE_MSG_NONE};
}

#endif // PX_LINUX_CONSOLE_MESSAGE_C
