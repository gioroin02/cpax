#include "../export.h"
#include "../../time/export.h"
#include "../../structure/export.h"

#include <stdlib.h>

#include <time.h>
#include <math.h>

#define PX_COLOR_RGB_UNITS pxas(pxiword, 3)

typedef union PxColorRGB
{
    struct
    {
        pxu8 r, g, b;
    };

    pxu8 items[PX_COLOR_RGB_UNITS];
}
PxColorRGB;

pxb8
pxColorRGBIsEqual(PxColorRGB* self, PxColorRGB* value)
{
    if (self == 0 || value == 0) return 0;

    if (self->r != value->r) return 0;
    if (self->g != value->g) return 0;
    if (self->b != value->b) return 0;

    return 1;
}

typedef struct PxConsoleCell
{
    pxi32      unicode;
    PxColorRGB front;
    PxColorRGB back;
}
PxConsoleCell;

typedef struct PxConsoleFrame
{
    PxArray items;

    pxiword width;
    pxiword height;
    pxb8    dirty;
}
PxConsoleFrame;

PxConsoleFrame
pxConsoleFrameMake(PxArena* arena, pxiword width, pxiword height)
{
    PxConsoleFrame result = {0};

    if (width <= 0 || height <= 0) return result;

    result.items = pxArrayReserve(arena,
        PxConsoleCell, width * height);

    if (result.items.length > 0) {
        pxArrayFill(&result.items);

        result.width  = width;
        result.height = height;
    }

    return result;
}

pxb8
pxConsoleFrameIsDirty(PxConsoleFrame* self)
{
    return self->dirty != 0 ? 1 : 0;
}

pxb8
pxConsoleFrameRead(PxConsoleFrame* self, pxiword x, pxiword y, PxConsoleCell* value)
{
    if (x < 0 || x >= self->width)  return 0;
    if (y < 0 || y >= self->height) return 0;

    pxiword index = x + self->width * y;

    return pxArrayRead(&self->items,
        index, PxConsoleCell, value);
}

PxConsoleCell
pxConsoleFrameReadOr(PxConsoleFrame* self, pxiword x, pxiword y, PxConsoleCell value)
{
    pxConsoleFrameRead(self, x, y, &value);

    return value;
}

pxb8
pxConsoleFrameUpdate(PxConsoleFrame* self, pxiword x, pxiword y, PxConsoleCell value)
{
    if (x < 0 || x >= self->width)  return 0;
    if (y < 0 || y >= self->height) return 0;

    pxiword index = x + self->width * y;

    self->dirty = 1;

    return pxArrayUpdate(&self->items,
        index, PxConsoleCell, &value);
}

pxb8
pxConsoleFrameReset(PxConsoleFrame* self, pxi32 unicode, PxColorRGB front, PxColorRGB back)
{
    if (unicode < 32) unicode = 32;

    PxConsoleCell item = {
        .unicode = unicode,
        .front   = front,
        .back    = back,
    };

    for (pxiword j = 0; j < self->height; j += 1) {
        for (pxiword i = 0; i < self->width; i += 1) {
            if (pxConsoleFrameUpdate(self, i, j, item) == 0)
                return 0;
        }
    }

    return 1;
}

pxb8
pxConsoleFramePaint(PxConsoleFrame* self, pxiword x, pxiword y, pxi32 unicode, PxColorRGB front, PxColorRGB back)
{
    if (unicode < 32) unicode = 32;

    PxConsoleCell item = {
        .unicode = unicode,
        .front   = front,
        .back    = back,
    };

    return pxConsoleFrameUpdate(self, x, y, item);
}

void
pxConsoleWriteFrame(PxWriter* self, PxArena* arena, PxConsoleFrame* frame)
{
    PxConsoleCell item = pxConsoleFrameReadOr(frame,
        0, 0, (PxConsoleCell) {0});;

    PxColorRGB front = item.front;
    PxColorRGB back  = item.back;

    pxConsoleWriteList(self, arena, 0, 3, (PxConsoleCmd[]) {
        pxConsoleCmdCursorPlace(0, 0),
        pxConsoleCmdStyleRGBFront(front.r, front.g, front.b),
        pxConsoleCmdStyleRGBBack(back.r, back.g, back.b),
    });

    for (pxiword j = 0; j < frame->height; j += 1) {
        for (pxiword i = 0; i < frame->width; i += 1) {
            item = pxConsoleFrameReadOr(frame, i, j, (PxConsoleCell) {0});

            if (pxColorRGBIsEqual(&front, &item.front) == 0) {
                front = item.front;

                pxConsoleWriteCmd(self, arena,
                    pxConsoleCmdStyleRGBFront(front.r, front.g, front.b));
            }

            if (pxColorRGBIsEqual(&back, &item.back) == 0) {
                back = item.back;

                pxConsoleWriteCmd(self, arena,
                    pxConsoleCmdStyleRGBBack(back.r, back.g, back.b));
            }

            pxConsoleWriteCmd(self, arena, pxConsoleCmdUnicode(item.unicode));
        }

        pxConsoleWriteCmd(self, arena, pxConsoleCmdCursorPlace(0, j + 1));
    }
}

typedef struct GameState
{
    pxu8 x, y;

    PxColorRGB front;
    PxColorRGB back;

    pxb8 move_left  : 1;
    pxb8 move_right : 1;
    pxb8 move_up    : 1;
    pxb8 move_down  : 1;

}
GameState;

int
main(int argc, char** argv)
{
    srand(time(0));

    PxArena arena = pxMemoryReserve(32);

    PxConsole console = pxConsoleCreate(&arena);
    PxReader  reader  = pxConsoleReader(console, &arena, 4 * PX_MEMORY_KIB);
    PxWriter  writer  = pxConsoleWriter(console, &arena, 8 * PX_MEMORY_KIB);

    PxConsoleMsg message = {0};

    PxConsoleFrame frame = pxConsoleFrameMake(&arena, 30, 10);

    pxConsoleSetMode(console, PX_CONSOLE_MODE_MESSAGE);

    GameState game = {
        .front = {.r = 128, .g = 128, .b = 128},
    };

    pxConsoleWriteList(&writer, &arena, 0, 2, (PxConsoleCmd[]) {
        pxConsoleCmdReset(),
        pxConsoleCmdCursorHide(),
    });

    pxWriterFlush(&writer);

    pxb8 active = 1;

    PxClock clock = pxClockCreate(&arena);

    pxf32 slice   = 1.0 / 64.0;
    pxf32 elapsed = 0;

    for (pxiword i = 0; active != 0; i += 1) {
        elapsed += pxClockElapsed(clock);

        do {
            message = pxConsolePollMsg(&reader, &arena);

            switch (message.type) {
                case PX_CONSOLE_MSG_KEYBD_PRESS: {
                    if (message.keybd_press.button == PX_CONSOLE_KEYBD_ESCAPE)
                        active = 0;

                    switch (message.keybd_press.button) {
                        case PX_CONSOLE_KEYBD_A: game.move_left  = 1; break;
                        case PX_CONSOLE_KEYBD_D: game.move_right = 1; break;
                        case PX_CONSOLE_KEYBD_W: game.move_up    = 1; break;
                        case PX_CONSOLE_KEYBD_S: game.move_down  = 1; break;

                        case PX_CONSOLE_KEYBD_ARROW_LEFT:  game.move_left  = 1; break;
                        case PX_CONSOLE_KEYBD_ARROW_RIGHT: game.move_right = 1; break;
                        case PX_CONSOLE_KEYBD_ARROW_UP:    game.move_up    = 1; break;
                        case PX_CONSOLE_KEYBD_ARROW_DOWN:  game.move_down  = 1; break;

                        default: break;
                    }
                } break;

                case PX_CONSOLE_MSG_KEYBD_RELEASE: {
                    switch (message.keybd_release.button) {
                        case PX_CONSOLE_KEYBD_A: game.move_left  = 0; break;
                        case PX_CONSOLE_KEYBD_D: game.move_right = 0; break;
                        case PX_CONSOLE_KEYBD_W: game.move_up    = 0; break;
                        case PX_CONSOLE_KEYBD_S: game.move_down  = 0; break;

                        case PX_CONSOLE_KEYBD_ARROW_LEFT:  game.move_left  = 0; break;
                        case PX_CONSOLE_KEYBD_ARROW_RIGHT: game.move_right = 0; break;
                        case PX_CONSOLE_KEYBD_ARROW_UP:    game.move_up    = 0; break;
                        case PX_CONSOLE_KEYBD_ARROW_DOWN:  game.move_down  = 0; break;

                        default: break;
                    }
                } break;

                default: break;
            }
        } while (message.type != PX_CONSOLE_MSG_NONE);

        if (elapsed >= slice) {
            pxu8 x = game.x + game.move_right - game.move_left;
            pxu8 y = game.y + game.move_down  - game.move_up;

            if (x >= 0 && x < frame.width)  game.x = x;
            if (y >= 0 && y < frame.height) game.y = y;

            pxf32 comp_r = (1 + sin(i * 0.0001 + 3)) * 0.5;
            pxf32 comp_g = (1 + sin(i * 0.0001 + 5)) * 0.5;
            pxf32 comp_b = (1 + sin(i * 0.0001 + 7)) * 0.5;

            game.back.r = pxas(pxu8, comp_r * 256);
            game.back.g = pxas(pxu8, comp_g * 256);
            game.back.b = pxas(pxu8, comp_b * 256);

            pxConsoleFrameReset(&frame,
                0, game.front, game.back);

            pxConsoleFramePaint(&frame, game.x, game.y,
                PX_ASCII_SHARP, (PxColorRGB) {0}, game.back);

            pxConsoleWriteFrame(&writer, &arena, &frame);
            pxWriterFlush(&writer);

            elapsed -= slice;
        }
    }

    pxConsoleWriteCmd(&writer, &arena, pxConsoleCmdReset());
    pxWriterFlush(&writer);

    pxConsoleSetMode(console, PX_CONSOLE_MODE_DEFAULT);
}
