#include "../export.h"
#include "../../structure/export.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct PxConsoleKeybdState
{
    pxb8 move_left  : 1;
    pxb8 move_right : 1;
    pxb8 move_up    : 1;
    pxb8 move_down  : 1;

}
PxConsoleKeybdState;

typedef struct PxConsoleCell
{
    pxu8 symbol;
    pxu8 color;
}
PxConsoleCell;

typedef struct PxConsoleBuffer
{
    PxArray items;

    pxiword width;
    pxiword height;

    pxu8 color;
}
PxConsoleBuffer;

PxConsoleBuffer
pxConsoleBufferMake(PxArena* arena, pxiword width, pxiword height)
{
    if (width <= 0 || height <= 0)
        return (PxConsoleBuffer) {0};

    PxArray items =
        pxArrayReserve(arena, PxConsoleCell, width * height);

    if (items.length <= 0)
        return (PxConsoleBuffer) {0};

    pxArrayFill(&items);

    return (PxConsoleBuffer) {
        .items  = items,
        .width  = width,
        .height = height,
    };
}

void
pxConsoleBufferReset(PxConsoleBuffer* self, pxu8 symbol, pxu8 foreground, pxu8 background)
{
    pxArrayFill(&self->items);

    PxConsoleCell item = {
        .symbol = symbol,
        .color  = foreground,
    };

    for (pxiword j = 0; j < self->height; j += 1) {
        for (pxiword i = 0; i < self->width; i += 1) {
            pxiword index = self->width * j + i;

            pxArrayUpdate(&self->items,
                index, PxConsoleCell, &item);
        }
    }

    self->color = background;
}

pxb8
pxConsoleBufferPaint(PxConsoleBuffer* self, pxiword x, pxiword y, pxu8 symbol, pxu8 color)
{
    pxiword index = self->width * y + x;

    PxConsoleCell item = {
        .symbol = symbol,
        .color  = color,
    };

    return pxArrayUpdate(&self->items,
        index, PxConsoleCell, &item);
}

void
pxConsoleApply(PxConsole self, PxConsoleBuffer* buffer)
{
    fprintf(stdout, "\033[H\033[48;5;%um", buffer->color);

    for (pxu8 j = 0; j < buffer->height; j += 1) {
        for (pxu8 i = 0; i < buffer->width; i += 1) {
            PxConsoleCell item = {0};

            pxiword index = buffer->width * j + i;

            pxArrayRead(&buffer->items, index, PxConsoleCell, &item);

            fprintf(stdout, "\033[38;5;%um%c",
                item.color, item.symbol);
        }

        fprintf(stdout, "\033[%u;1H", j);
    }

    fflush(stdout);
}

void
pxConsoleReset(PxConsole self)
{
    fprintf(stdout, "\033[0m\033c");

    fflush(stdout);
}

void
pxConsoleShowCursor(PxConsole self, pxb8 state)
{
    switch (state) {
        case 0:
            fprintf(stdout, "\033[?25l");
        break;

        default:
            fprintf(stdout, "\033[?25h");
        break;
    }

    fflush(stdin);
}

int
main(int argc, char** argv)
{
    PxArena arena = pxMemoryReserve(16);

    #define BUFFERS 2

    PxConsoleBuffer buffers[BUFFERS] = {
        pxConsoleBufferMake(&arena, 60, 20),
        pxConsoleBufferMake(&arena, 60, 20),
    };

    pxiword          bufidx = 0;
    PxConsoleBuffer* buffer = &buffers[bufidx];

    PxConsole console = pxConsoleCreate(&arena, PX_MEMORY_KIB);

    pxConsoleInputModeRaw(console);

    pxu8 x          = 1;
    pxu8 y          = 1;
    pxu8 foreground = 0;
    pxu8 background = 128;

    PxConsoleKeybdState keybd = {0};

    pxConsoleReset(console);
    pxConsoleShowCursor(console, 0);

    pxb8 active = 1;

    srand(time(0));

    for (pxiword i = 0; active != 0; i += 1) {
        PxConsoleEvent event = pxConsoleReadEvent(console);

        keybd.move_left  = 0;
        keybd.move_right = 0;
        keybd.move_up    = 0;
        keybd.move_down  = 0;

        switch (event.type) {
            case PX_CONSOLE_EVENT_KEYBD_PRESS: {
                if (event.keybd_press.button == PX_CONSOLE_KEYBD_ESCAPE)
                    active = 0;

                switch (event.keybd_press.button) {
                    case PX_CONSOLE_KEYBD_A: keybd.move_left  = 1; break;
                    case PX_CONSOLE_KEYBD_D: keybd.move_right = 1; break;
                    case PX_CONSOLE_KEYBD_W: keybd.move_up    = 1; break;
                    case PX_CONSOLE_KEYBD_S: keybd.move_down  = 1; break;

                    case PX_CONSOLE_KEYBD_ARROW_LEFT:  keybd.move_left  = 1; break;
                    case PX_CONSOLE_KEYBD_ARROW_RIGHT: keybd.move_right = 1; break;
                    case PX_CONSOLE_KEYBD_ARROW_UP:    keybd.move_up    = 1; break;
                    case PX_CONSOLE_KEYBD_ARROW_DOWN:  keybd.move_down  = 1; break;

                    default: break;
                }
            } break;

            default: break;
        }

        pxi8 dx = keybd.move_right - keybd.move_left;
        pxi8 dy = keybd.move_down  - keybd.move_up;

        if (dx != 0 || dy != 0) {
            x = pxClamp(x + dx, 1, buffer->width  + 1);
            y = pxClamp(y + dy, 1, buffer->height + 1);
        }

        foreground = (foreground + 1)   % 256;
        background = (foreground + 128) % 256;

        if (i % 5000 == 0) {
            pxConsoleBufferReset(buffer, PX_ASCII_SPACE, 0, background);
            pxConsoleBufferPaint(buffer, x, y, PX_ASCII_SHARP, foreground);

            pxConsoleApply(console, buffer);

            bufidx = (bufidx + 1) % BUFFERS;
            buffer = &buffers[bufidx];
        }
    }

    pxConsoleReset(console);

    pxConsoleInputModeRestore(console);
}
