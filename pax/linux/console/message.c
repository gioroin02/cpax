#ifndef PX_LINUX_CONSOLE_MESSAGE_C
#define PX_LINUX_CONSOLE_MESSAGE_C

#include "message.h"

PxConsoleMsg
pxLinuxConsoleReadMsg(PxInput* self, PxArena* arena)
{
    return (PxConsoleMsg) {.type = PX_CONSOLE_MSG_NONE};
}

PxConsoleMsg
pxLinuxConsolePollMsg(PxInput* self, PxArena* arena)
{
    return (PxConsoleMsg) {.type = PX_CONSOLE_MSG_NONE};
}

#endif // PX_LINUX_CONSOLE_MESSAGE_C
