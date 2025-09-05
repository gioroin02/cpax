#ifndef PX_LINUX_CONSOLE_CONSOLE_C
#define PX_LINUX_CONSOLE_CONSOLE_C

#include "console.h"

#include <unistd.h>
#include <errno.h>

#include <termios.h>

typedef struct termios PxTermIO;

struct PxLinuxConsole
{
    PxTermIO       inout;
    PxConsoleEvent last;
};

pxb8
pxLinuxEscapeSequence(PxString8 string, PxConsoleEvent* event)
{
    if (string.length <= 0 || event == 0)
        return string.length;

    switch (string.memory[0]) {
        case PX_ASCII_LOWER_A:
        case PX_ASCII_LOWER_B:
        case PX_ASCII_LOWER_C:
        case PX_ASCII_LOWER_D:
        case PX_ASCII_LOWER_E:
        case PX_ASCII_LOWER_F:
        case PX_ASCII_LOWER_G:
        case PX_ASCII_LOWER_H:
        case PX_ASCII_LOWER_I:
        case PX_ASCII_LOWER_J:
        case PX_ASCII_LOWER_K:
        case PX_ASCII_LOWER_L:
        case PX_ASCII_LOWER_M:
        case PX_ASCII_LOWER_N:
        case PX_ASCII_LOWER_O:
        case PX_ASCII_LOWER_P:
        case PX_ASCII_LOWER_Q:
        case PX_ASCII_LOWER_R:
        case PX_ASCII_LOWER_S:
        case PX_ASCII_LOWER_T:
        case PX_ASCII_LOWER_U:
        case PX_ASCII_LOWER_V:
        case PX_ASCII_LOWER_W:
        case PX_ASCII_LOWER_X:
        case PX_ASCII_LOWER_Y:
        case PX_ASCII_LOWER_Z: {
            event->type = PX_CONSOLE_EVENT_KEYBD_PRESS;

            event->keybd_press.button = PX_CONSOLE_KEYBD_A +
                string.memory[0] - PX_ASCII_LOWER_A;

            event->keybd_press.unicode = string.memory[0];
            event->keybd_press.modifs  = PX_CONSOLE_MODIF_ALT;
        } break;

        case PX_ASCII_UPPER_A:
        case PX_ASCII_UPPER_B:
        case PX_ASCII_UPPER_C:
        case PX_ASCII_UPPER_D:
        case PX_ASCII_UPPER_E:
        case PX_ASCII_UPPER_F:
        case PX_ASCII_UPPER_G:
        case PX_ASCII_UPPER_H:
        case PX_ASCII_UPPER_I:
        case PX_ASCII_UPPER_J:
        case PX_ASCII_UPPER_K:
        case PX_ASCII_UPPER_L:
        case PX_ASCII_UPPER_M:
        case PX_ASCII_UPPER_N:
        case PX_ASCII_UPPER_O:
        case PX_ASCII_UPPER_P:
        case PX_ASCII_UPPER_Q:
        case PX_ASCII_UPPER_R:
        case PX_ASCII_UPPER_S:
        case PX_ASCII_UPPER_T:
        case PX_ASCII_UPPER_U:
        case PX_ASCII_UPPER_V:
        case PX_ASCII_UPPER_W:
        case PX_ASCII_UPPER_X:
        case PX_ASCII_UPPER_Y:
        case PX_ASCII_UPPER_Z: {
            event->type = PX_CONSOLE_EVENT_KEYBD_PRESS;

            event->keybd_press.button = PX_CONSOLE_KEYBD_A +
                string.memory[0] - PX_ASCII_UPPER_A;

            event->keybd_press.unicode = string.memory[0];

            event->keybd_press.modifs =
                PX_CONSOLE_MODIF_ALT | PX_CONSOLE_MODIF_SHIFT;
        } break;

        default: break;
    }

    return 1;
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
pxLinuxConsoleWrite(PxLinuxConsole* self, PxBuffer8* buffer)
{
    pxBuffer8Normalize(buffer);

    pxu8*   memory = buffer->memory;
    pxiword size   = buffer->size;

    if (size <= 0) return 0;

    pxiword temp = pxLinuxConsoleWriteMemory(self, memory, size, 1);

    buffer->size -= temp;
    buffer->head  = (buffer->head + temp) % buffer->length;

    return temp;
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
pxLinuxConsoleRead(PxLinuxConsole* self, PxBuffer8* buffer)
{
    pxBuffer8Normalize(buffer);

    pxu8*   memory = buffer->memory + buffer->size;
    pxiword size   = buffer->length - buffer->size;

    if (size <= 0) return 0;

    pxiword temp = pxLinuxConsoleReadMemory(self, memory, size, 1);

    buffer->size += temp;
    buffer->tail  = (buffer->tail + temp) % buffer->length;

    return temp;
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
pxLinuxConsoleReadEvent(PxLinuxConsole* self, PxBuffer8* buffer)
{
    PxConsoleEvent result = {.type = PX_CONSOLE_EVENT_NONE};

    if (self->last.type == PX_CONSOLE_EVENT_KEYBD_PRESS) {
        result.type = PX_CONSOLE_EVENT_KEYBD_RELEASE;

	result.keybd_release.button  = self->last.keybd_press.button;
	result.keybd_release.unicode = self->last.keybd_press.unicode;
	result.keybd_release.modifs  = self->last.keybd_press.modifs;

        self->last = result;

	return result;
    }

    pxiword size = pxLinuxConsoleRead(self, buffer);

    if (buffer->size <= 0) return result;

    switch (buffer->memory[0]) {
        case '\x1b': {
            PxString8 string = {0};

	    string.memory = buffer->memory;
	    string.length = buffer->size;

            if (size == 1) {
                result.type = PX_CONSOLE_EVENT_KEYBD_PRESS;

                result.keybd_press.button  = PX_CONSOLE_KEYBD_ESCAPE;
                result.keybd_press.unicode = PX_ASCII_ESCAPE;
                result.keybd_press.modifs  = 0;
            } else
                size = pxLinuxEscapeSequence(string, &result) + 1;

	    pxBuffer8DropHead(buffer, size);
        } break;

        default: {
            pxi32 unicode = 0;

            size = pxUtf8ReadMemory8Forw(
                buffer->memory, buffer->size, 0, &unicode);

            pxBuffer8DropHead(buffer, size);

            if (size == 0) return result;

            result.type = PX_CONSOLE_EVENT_KEYBD_PRESS;

            result.keybd_press.button  = PX_CONSOLE_KEYBD_NONE;
            result.keybd_press.unicode = unicode;
            result.keybd_press.modifs  = 0;
        } break;
    }

    self->last = result;

    return result;
}

#endif // PX_LINUX_CONSOLE_CONSOLE_C
