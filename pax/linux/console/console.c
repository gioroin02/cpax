#ifndef PX_LINUX_CONSOLE_CONSOLE_C
#define PX_LINUX_CONSOLE_CONSOLE_C

#include "console.h"

// TODO
#include <stdio.h>

#include <unistd.h>
#include <errno.h>

#include <termios.h>

typedef struct termios PxTermIO;

struct PxLinuxConsole
{
    PxTermIO       inout;
    PxConsoleEvent last;
};

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
pxLinuxConsoleKeybdModeRaw(PxLinuxConsole* self)
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

pxb8
pxLinuxConsoleKeybdModeRestore(PxLinuxConsole* self)
{
    int state = tcsetattr(STDIN_FILENO, TCSANOW, &self->inout);

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
pxLinuxConsoleReadEvent(PxLinuxConsole* self, PxArena* arena)
{
    PxConsoleEvent result = {.type = PX_CONSOLE_EVENT_NONE};

    switch (self->last.type) {
        case PX_CONSOLE_EVENT_KEYBD_PRESS: {
            pxiword button  = self->last.keybd_press.button;
            pxuword modifs  = self->last.keybd_press.modifs;
            pxi32   unicode = self->last.keybd_press.unicode;

            result = pxConsoleEventKeybdRelease(button, modifs, unicode);

            self->last = result;

            return result;
        } break;

        default: break;
    }

    pxiword offset = pxArenaOffset(arena);
    pxu8*   memory = pxArenaReserveMemory(arena, PX_MEMORY_KIB, 1);

    pxiword size = pxLinuxConsoleReadMemory(self,
        memory, PX_MEMORY_KIB, 1);

    switch (memory[0]) {
        case PX_ASCII_ESCAPE:
            PxConsoleSequence escape = {0};
            PxString8         string = {.memory = memory, .length = size};

            if (pxConsoleSequenceFromString8(&escape, string) == 0)
                return result;

            printf("func = %c\r\n", escape.func);

                for (pxiword i = 0; i < escape.size; i += 1)
                    printf("args = %u\r\n", escape.args[i]);

            printf("\r\n");

            switch (escape.func) {
                case 0: {
                    pxiword button  = PX_CONSOLE_KEYBD_ESCAPE;
                    pxuword modifs  = 0;
                    pxi32   unicode = PX_ASCII_ESCAPE;

                    result = pxConsoleEventKeybdPress(
                        button, modifs, unicode);
                } break;

                default: break;
            }
        break;

        default: {
            pxiword button  = PX_CONSOLE_KEYBD_NONE;
            pxuword modifs  = 0;
            pxi32   unicode = 0;

            pxiword units = pxUtf8ReadMemory8Forw(
                memory, size, 0, &unicode);

            if (units <= 0) break;

            result = pxConsoleEventKeybdPress(
                button, modifs, unicode);
        } break;
    }

    self->last = result;

    pxArenaRewind(arena, offset);

    return result;
}

#endif // PX_LINUX_CONSOLE_CONSOLE_C
