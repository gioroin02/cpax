#ifndef PX_LINUX_CONSOLE_CONSOLE_C
#define PX_LINUX_CONSOLE_CONSOLE_C

#include "console.h"

#include <unistd.h>
#include <errno.h>

#include <termios.h>

typedef struct termios PxTermIO;

struct PxLinuxConsole
{
    PxTermIO inout;
};

pxb8
pxLinuxEscapeSequence(pxu8* memory, pxiword length, PxConsoleEvent* event)
{
    if (length <= 0 || event == 0)
        return 0;

    switch (memory[0]) {
        case PX_ASCII_SQUARE_LEFT: {
            if (pxMemoryIsEqual(memory + 1, "A", 1, 1) != 0) {
                event->type = PX_CONSOLE_EVENT_KEYBD_PRESS;

                event->keybd_press.button  = PX_CONSOLE_KEYBD_ARROW_UP;
                event->keybd_press.unicode = 0;
                event->keybd_press.modifs  = 0;
            }

            if (pxMemoryIsEqual(memory + 1, "B", 1, 1) != 0) {
                event->type = PX_CONSOLE_EVENT_KEYBD_PRESS;

                event->keybd_press.button  = PX_CONSOLE_KEYBD_ARROW_DOWN;
                event->keybd_press.unicode = 0;
                event->keybd_press.modifs  = 0;
            }

            if (pxMemoryIsEqual(memory + 1, "C", 1, 1) != 0) {
                event->type = PX_CONSOLE_EVENT_KEYBD_PRESS;

                event->keybd_press.button  = PX_CONSOLE_KEYBD_ARROW_RIGHT;
                event->keybd_press.unicode = 0;
                event->keybd_press.modifs  = 0;
            }

            if (pxMemoryIsEqual(memory + 1, "D", 1, 1) != 0) {
                event->type = PX_CONSOLE_EVENT_KEYBD_PRESS;

                event->keybd_press.button  = PX_CONSOLE_KEYBD_ARROW_LEFT;
                event->keybd_press.unicode = 0;
                event->keybd_press.modifs  = 0;
            }

            if (pxMemoryIsEqual(memory + 1, "H", 1, 1) != 0) {
                event->type = PX_CONSOLE_EVENT_KEYBD_PRESS;

                event->keybd_press.button  = PX_CONSOLE_KEYBD_HOME;
                event->keybd_press.unicode = 0;
                event->keybd_press.modifs  = 0;
            }

            if (pxMemoryIsEqual(memory + 1, "F", 1, 1) != 0) {
                event->type = PX_CONSOLE_EVENT_KEYBD_PRESS;

                event->keybd_press.button  = PX_CONSOLE_KEYBD_END;
                event->keybd_press.unicode = 0;
                event->keybd_press.modifs  = 0;
            }

            if (pxMemoryIsEqual(memory + 1, "5~", 2, 1) != 0) {
                event->type = PX_CONSOLE_EVENT_KEYBD_PRESS;

                event->keybd_press.button  = PX_CONSOLE_KEYBD_PAGE_UP;
                event->keybd_press.unicode = 0;
                event->keybd_press.modifs  = 0;
            }

            if (pxMemoryIsEqual(memory + 1, "6~", 2, 1) != 0) {
                event->type = PX_CONSOLE_EVENT_KEYBD_PRESS;

                event->keybd_press.button  = PX_CONSOLE_KEYBD_PAGE_UP;
                event->keybd_press.unicode = 0;
                event->keybd_press.modifs  = 0;
            }
        } break;

        default: break;
    }

    return 0;
}

PxLinuxConsole*
pxLinuxConsoleCreate(PxArena* arena)
{
    pxiword offset = pxArenaOffset(arena);

    PxLinuxConsole* result =
        pxArenaReserve(arena, PxLinuxConsole, 1);

    if (result != 0) {
        int state = tcgetattr(STDIN_FILENO, &result->inout);

        if (state != -1)
            return result;
    }

    pxArenaRewind(arena, offset);

    return 0;
}

pxb8
pxLinuxConsoleSetModeDefault(PxLinuxConsole* self)
{
    int state = tcsetattr(STDIN_FILENO, TCSANOW, &self->inout);

    if (state != -1) return 1;

    return 0;
}

pxb8
pxLinuxConsoleSetModeRaw(PxLinuxConsole* self)
{
    PxTermIO inout = self->inout;

    inout.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
    inout.c_oflag &= ~(OPOST);
    inout.c_cflag |= CS8;
    inout.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);

    inout.c_cc[VMIN]  = 0;
    inout.c_cc[VTIME] = 1;

    int state = tcsetattr(STDIN_FILENO, TCSAFLUSH, &inout);

    if (state != -1) return 1;

    return 0;
}

pxiword
pxLinuxConsoleWriteMemory(PxLinuxConsole* self, void* memory, pxiword amount, pxiword stride)
{
    pxiword length = amount * stride;
    pxiword temp   = 0;

    for (pxiword i = 0; i < length;) {
        char* mem = pxCast(char*, memory + i);
        int   len = pxCast(int,   length - i);

        do {
            temp = write(STDOUT_FILENO, mem, len);
        } while (temp == -1 && errno == EINTR);

        if (temp > 0 && temp <= length - i)
            i += temp;
        else
            return i;
    }

    return length;
}

pxiword
pxLinuxConsoleReadMemory(PxLinuxConsole* self, void* memory, pxiword amount, pxiword stride)
{
    pxiword length = amount * stride;
    pxiword temp   = 0;

    char* mem = pxCast(char*, memory);
    int   len = pxCast(int,   length);

    do {
        temp = read(STDIN_FILENO, mem, len);
    } while (temp == -1 && errno == EINTR);

    if (temp > 0 && temp <= length)
        return temp;

    return 0;
}

PxConsoleEvent
pxLinuxConsoleNext(PxLinuxConsole* self, PxArena* arena)
{
    PxConsoleEvent result = {.type = PX_CONSOLE_EVENT_NONE};

    pxiword length = PX_MEMORY_KIB;
    pxu8*   memory = pxArenaReserveMemory(arena, length, 1);

    pxiword size =
        pxLinuxConsoleReadMemory(self, memory, length, 1);

    if (size <= 0) return result;

    switch (memory[0]) {
        case '\x1b': {
            if (size == 1) {
                result.type = PX_CONSOLE_EVENT_KEYBD_PRESS;

                result.keybd_press.button  = PX_CONSOLE_KEYBD_ESCAPE;
                result.keybd_press.unicode = memory[0];
            } else
                pxLinuxEscapeSequence(memory + 1, size - 1, &result);
        } break;

        default: {
            pxi32 unicode = 0;

            pxiword units = pxUtf8ReadMemory8Forw(
                memory, length, 0, &unicode);

            if (units == 0) return result;

            result.type = PX_CONSOLE_EVENT_KEYBD_PRESS;

            result.keybd_press.button  = PX_CONSOLE_KEYBD_NONE;
            result.keybd_press.unicode = unicode;
            result.keybd_press.modifs  = 0;
        } break;
    }

    return result;
}

#endif // PX_LINUX_CONSOLE_CONSOLE_C
