#ifndef PX_LINUX_CONSOLE_CONSOLE_C
#define PX_LINUX_CONSOLE_CONSOLE_C

#include "console.h"

#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

#include <termios.h>

typedef struct termios PxTermIO;

struct PxLinuxConsole
{
    PxTermIO       inout;
    PxConsoleEvent last;
    PxBuffer8      buffer;
};

pxuword
pxLinuxMapConsoleKeybdModifs(pxuword value)
{
    pxuword result = 0;

    if (value > 1 && value <= 8) {
        value -= 1;

        if ((value) & 1 != 0) result |= PX_CONSOLE_MODIF_SHIFT;
        if ((value) & 2 != 0) result |= PX_CONSOLE_MODIF_ALT;
        if ((value) & 4 != 0) result |= PX_CONSOLE_MODIF_CTRL;
    }

    return result;
}

pxiword
pxLinuxMapConsoleKeybdButton(pxi32 unicode)
{
    switch (unicode) {
        case PX_ASCII_LOWER_A: return PX_CONSOLE_KEYBD_A;
        case PX_ASCII_LOWER_B: return PX_CONSOLE_KEYBD_B;
        case PX_ASCII_LOWER_C: return PX_CONSOLE_KEYBD_C;
        case PX_ASCII_LOWER_D: return PX_CONSOLE_KEYBD_D;
        case PX_ASCII_LOWER_E: return PX_CONSOLE_KEYBD_E;
        case PX_ASCII_LOWER_F: return PX_CONSOLE_KEYBD_F;
        case PX_ASCII_LOWER_G: return PX_CONSOLE_KEYBD_G;
        case PX_ASCII_LOWER_H: return PX_CONSOLE_KEYBD_H;
        case PX_ASCII_LOWER_I: return PX_CONSOLE_KEYBD_I;
        case PX_ASCII_LOWER_J: return PX_CONSOLE_KEYBD_J;
        case PX_ASCII_LOWER_K: return PX_CONSOLE_KEYBD_K;
        case PX_ASCII_LOWER_L: return PX_CONSOLE_KEYBD_L;
        case PX_ASCII_LOWER_M: return PX_CONSOLE_KEYBD_M;
        case PX_ASCII_LOWER_N: return PX_CONSOLE_KEYBD_N;
        case PX_ASCII_LOWER_O: return PX_CONSOLE_KEYBD_O;
        case PX_ASCII_LOWER_P: return PX_CONSOLE_KEYBD_P;
        case PX_ASCII_LOWER_Q: return PX_CONSOLE_KEYBD_Q;
        case PX_ASCII_LOWER_R: return PX_CONSOLE_KEYBD_R;
        case PX_ASCII_LOWER_S: return PX_CONSOLE_KEYBD_S;
        case PX_ASCII_LOWER_T: return PX_CONSOLE_KEYBD_T;
        case PX_ASCII_LOWER_U: return PX_CONSOLE_KEYBD_U;
        case PX_ASCII_LOWER_V: return PX_CONSOLE_KEYBD_V;
        case PX_ASCII_LOWER_W: return PX_CONSOLE_KEYBD_W;
        case PX_ASCII_LOWER_X: return PX_CONSOLE_KEYBD_X;
        case PX_ASCII_LOWER_Y: return PX_CONSOLE_KEYBD_Y;
        case PX_ASCII_LOWER_Z: return PX_CONSOLE_KEYBD_Z;

        case PX_ASCII_UPPER_A: return PX_CONSOLE_KEYBD_A;
        case PX_ASCII_UPPER_B: return PX_CONSOLE_KEYBD_B;
        case PX_ASCII_UPPER_C: return PX_CONSOLE_KEYBD_C;
        case PX_ASCII_UPPER_D: return PX_CONSOLE_KEYBD_D;
        case PX_ASCII_UPPER_E: return PX_CONSOLE_KEYBD_E;
        case PX_ASCII_UPPER_F: return PX_CONSOLE_KEYBD_F;
        case PX_ASCII_UPPER_G: return PX_CONSOLE_KEYBD_G;
        case PX_ASCII_UPPER_H: return PX_CONSOLE_KEYBD_H;
        case PX_ASCII_UPPER_I: return PX_CONSOLE_KEYBD_I;
        case PX_ASCII_UPPER_J: return PX_CONSOLE_KEYBD_J;
        case PX_ASCII_UPPER_K: return PX_CONSOLE_KEYBD_K;
        case PX_ASCII_UPPER_L: return PX_CONSOLE_KEYBD_L;
        case PX_ASCII_UPPER_M: return PX_CONSOLE_KEYBD_M;
        case PX_ASCII_UPPER_N: return PX_CONSOLE_KEYBD_N;
        case PX_ASCII_UPPER_O: return PX_CONSOLE_KEYBD_O;
        case PX_ASCII_UPPER_P: return PX_CONSOLE_KEYBD_P;
        case PX_ASCII_UPPER_Q: return PX_CONSOLE_KEYBD_Q;
        case PX_ASCII_UPPER_R: return PX_CONSOLE_KEYBD_R;
        case PX_ASCII_UPPER_S: return PX_CONSOLE_KEYBD_S;
        case PX_ASCII_UPPER_T: return PX_CONSOLE_KEYBD_T;
        case PX_ASCII_UPPER_U: return PX_CONSOLE_KEYBD_U;
        case PX_ASCII_UPPER_V: return PX_CONSOLE_KEYBD_V;
        case PX_ASCII_UPPER_W: return PX_CONSOLE_KEYBD_W;
        case PX_ASCII_UPPER_X: return PX_CONSOLE_KEYBD_X;
        case PX_ASCII_UPPER_Y: return PX_CONSOLE_KEYBD_Y;
        case PX_ASCII_UPPER_Z: return PX_CONSOLE_KEYBD_Z;

        case PX_ASCII_ZERO:  return PX_CONSOLE_KEYBD_ZERO;
        case PX_ASCII_ONE:   return PX_CONSOLE_KEYBD_ONE;
        case PX_ASCII_TWO:   return PX_CONSOLE_KEYBD_TWO;
        case PX_ASCII_THREE: return PX_CONSOLE_KEYBD_THREE;
        case PX_ASCII_FOUR:  return PX_CONSOLE_KEYBD_FOUR;
        case PX_ASCII_FIVE:  return PX_CONSOLE_KEYBD_FIVE;
        case PX_ASCII_SIX:   return PX_CONSOLE_KEYBD_SIX;
        case PX_ASCII_SEVEN: return PX_CONSOLE_KEYBD_SEVEN;
        case PX_ASCII_EIGHT: return PX_CONSOLE_KEYBD_EIGHT;
        case PX_ASCII_NINE:  return PX_CONSOLE_KEYBD_NINE;

        default: break;
    }

    return PX_CONSOLE_KEYBD_NONE;
}

PxConsoleEvent
pxLinuxMapConsoleKeybdEvent(pxi32 unicode)
{
    pxiword button = pxLinuxMapConsoleKeybdButton(unicode);
    pxuword modifs = 0;

    if (unicode >= PX_ASCII_UPPER_A && unicode <= PX_ASCII_UPPER_Z)
        modifs |= PX_CONSOLE_MODIF_SHIFT;

    return pxConsoleEventKeybdPress(button, modifs, unicode);
}

PxConsoleEvent
pxLinuxConsoleEventFromSequence(PxConsoleSequence* sequence)
{
    PxConsoleEvent result = {.type = PX_CONSOLE_EVENT_NONE};

    switch (sequence->func) {
        case PX_ASCII_NULL: {
            pxiword button  = pxLinuxMapConsoleKeybdButton(sequence->args[0]);
            pxuword modifs  = pxLinuxMapConsoleKeybdModifs(sequence->args[1]);
            pxi32   unicode = sequence->args[0];

            result = pxConsoleEventKeybdPress(
                button, modifs, unicode);
        } break;

        case PX_ASCII_CARRIAGE_RETURN: {
            result = pxConsoleEventKeybdPress(
                PX_CONSOLE_KEYBD_ENTER, 0, sequence->func);
        } break;

        case PX_ASCII_BACK_SPACE: {
            result = pxConsoleEventKeybdPress(
                PX_CONSOLE_KEYBD_BACK_SPACE, 0, sequence->func);
        } break;

        case PX_ASCII_ESCAPE: {
            result = pxConsoleEventKeybdPress(
                PX_CONSOLE_KEYBD_ESCAPE, 0, PX_ASCII_ESCAPE);
        } break;

        case PX_ASCII_UPPER_A: {
            pxuword modifs = 0;

            if (sequence->size >= 2)
                modifs = pxLinuxMapConsoleKeybdModifs(sequence->args[1]);

            result = pxConsoleEventKeybdPress(
                PX_CONSOLE_KEYBD_ARROW_UP, modifs, 0);
        } break;

        case PX_ASCII_UPPER_B: {
            pxuword modifs = 0;

            if (sequence->size >= 2)
                modifs = pxLinuxMapConsoleKeybdModifs(sequence->args[1]);

            result = pxConsoleEventKeybdPress(
                PX_CONSOLE_KEYBD_ARROW_DOWN, modifs, 0);
        } break;

        case PX_ASCII_UPPER_C: {
            pxuword modifs = 0;

            if (sequence->size >= 2)
                modifs = pxLinuxMapConsoleKeybdModifs(sequence->args[1]);

            result = pxConsoleEventKeybdPress(
                PX_CONSOLE_KEYBD_ARROW_RIGHT, modifs, 0);
        } break;

        case PX_ASCII_UPPER_D: {
            pxuword modifs = 0;

            if (sequence->size >= 2)
                modifs = pxLinuxMapConsoleKeybdModifs(sequence->args[1]);

            result = pxConsoleEventKeybdPress(
                PX_CONSOLE_KEYBD_ARROW_LEFT, modifs, 0);
        } break;

        case PX_ASCII_UPPER_H: {
            pxuword modifs = 0;

            if (sequence->size >= 2)
                modifs = pxLinuxMapConsoleKeybdModifs(sequence->args[1]);

            result = pxConsoleEventKeybdPress(
                PX_CONSOLE_KEYBD_HOME, modifs, 0);
        } break;

        case PX_ASCII_UPPER_F: {
            pxuword modifs = 0;

            if (sequence->size >= 2)
                modifs = pxLinuxMapConsoleKeybdModifs(sequence->args[1]);

            result = pxConsoleEventKeybdPress(
                PX_CONSOLE_KEYBD_END, modifs, 0);
        } break;

        case PX_ASCII_TILDE: {
            if (sequence->size <= 0) return result;

            pxiword button = PX_CONSOLE_KEYBD_NONE;
            pxuword modifs = 0;

            switch (sequence->args[0]) {
                case 5: button = PX_CONSOLE_KEYBD_PAGE_UP;   break;
                case 6: button = PX_CONSOLE_KEYBD_PAGE_DOWN; break;

                case 11: button = PX_CONSOLE_KEYBD_FUNC1; break;
                case 12: button = PX_CONSOLE_KEYBD_FUNC2; break;
                case 13: button = PX_CONSOLE_KEYBD_FUNC3; break;
                case 14: button = PX_CONSOLE_KEYBD_FUNC4; break;
                case 15: button = PX_CONSOLE_KEYBD_FUNC5; break;

                case 17: button = PX_CONSOLE_KEYBD_FUNC6;  break;
                case 18: button = PX_CONSOLE_KEYBD_FUNC7;  break;
                case 19: button = PX_CONSOLE_KEYBD_FUNC8;  break;
                case 20: button = PX_CONSOLE_KEYBD_FUNC9;  break;
                case 21: button = PX_CONSOLE_KEYBD_FUNC10; break;

                case 23: button = PX_CONSOLE_KEYBD_FUNC11; break;
                case 24: button = PX_CONSOLE_KEYBD_FUNC12; break;

                default: break;
            }

            if (sequence->size >= 2)
                modifs = pxLinuxMapConsoleKeybdModifs(sequence->args[1]);

            result = pxConsoleEventKeybdPress(button, modifs, 0);
        } break;

        default: break;
    }

    return result;
}

PxLinuxConsole*
pxLinuxConsoleCreate(PxArena* arena, pxiword length)
{
    pxiword offset = pxArenaOffset(arena);

    PxLinuxConsole* result =
        pxArenaReserve(arena, PxLinuxConsole, 1);

    if (result != 0) {
        result->buffer = pxBuffer8Reserve(arena, length);

        int state = tcgetattr(STDIN_FILENO, &result->inout);

        if (result->buffer.length > 0 && state != -1)
            return result;
    }

    pxArenaRewind(arena, offset);

    return 0;
}

pxb8
pxLinuxConsoleModeRaw(PxLinuxConsole* self)
{
    PxTermIO inout = self->inout;

    inout.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
    inout.c_oflag &= ~(OPOST);
    inout.c_cflag |= CS8;
    inout.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);

    inout.c_cc[VMIN]  = 0;
    inout.c_cc[VTIME] = 1;

    int state = 0;

    do {
        state = tcsetattr(STDIN_FILENO, TCSAFLUSH, &inout);
    } while (state == -1 && errno == EINTR);

    if (state == -1) return 0;

    do {
        state = fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);
    } while (state == -1 && errno == EINTR);

    if (state == -1) return 0;

    return 1;
}

pxb8
pxLinuxConsoleModeRestore(PxLinuxConsole* self)
{
    int state = 0;

    do {
        state = tcsetattr(STDIN_FILENO, TCSANOW, &self->inout);
    } while (state == -1 && errno == EINTR);

    if (state == -1) return 0;

    do {
        state = fcntl(STDIN_FILENO, F_SETFL, ~O_NONBLOCK);
    } while (state == -1 && errno == EINTR);

    if (state == -1) return 0;

    return 1;
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
pxLinuxConsoleReadEvent(PxLinuxConsole* self)
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

    pxBuffer8Normalize(&self->buffer);

    pxu8*   memory = self->buffer.memory + self->buffer.size;
    pxiword length = self->buffer.length - self->buffer.size;

    PxString8 string = {
        .memory = self->buffer.memory,
        .length = self->buffer.size,
    };

    pxiword size = pxLinuxConsoleReadMemory(self, memory, length, 1);

    self->buffer.size += size;
    self->buffer.tail  = (self->buffer.tail + size) % self->buffer.length;

    if (self->buffer.size <= 0) return result;

    PxConsoleSequence sequence = {0};

    size = pxConsoleSequenceFromString8(&sequence, string);

    if (size == 0) {
        pxi32 unicode = 0;

        size = pxUtf8ReadMemory8Forw(string.memory,
            string.length, 0, &unicode);

        if (size > 0)
            result = pxLinuxMapConsoleKeybdEvent(unicode);
    } else
        result = pxLinuxConsoleEventFromSequence(&sequence);

    pxBuffer8DropHead(&self->buffer, size);

    self->last = result;

    return result;
}

#endif // PX_LINUX_CONSOLE_CONSOLE_C
