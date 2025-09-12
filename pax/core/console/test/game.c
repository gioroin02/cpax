#include "../export.h"
#include "../../time/export.h"
#include "../../structure/export.h"

#define PX_COLOR_RGB_UNITS pxCast(pxiword, 3)

typedef union PxColorRGB
{
    struct
    {
        pxu8 r, g, b;
    };

    pxu8 items[PX_COLOR_RGB_UNITS];
}
PxColorRGB;

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
pxConsoleWriteFrame(PxWriter* self, PxConsoleFrame* frame)
{
    for (pxiword j = 0; j < frame->height; j += 1) {
        for (pxiword i = 0; i < frame->width; i += 1) {
            PxConsoleCell item =
                pxConsoleFrameReadOr(frame, i, j, (PxConsoleCell) {0});

            pxConsoleWriteCommand(self, pxConsoleCmdCursorPlace(i, j));

            pxConsoleWriteCommand(self,
                pxConsoleCmdStyleRGBFront(item.front.r, item.front.g, item.front.b));

            pxConsoleWriteCommand(self,
                pxConsoleCmdStyleRGBBack(item.back.r, item.back.g, item.back.b));

            pxConsoleWriteCommand(self, pxConsoleCmdUnicode(item.unicode));
        }

        pxWriterFlush(self);
    }
}

typedef struct PxConsoleGameState
{
    pxu8 x, y;

    PxColorRGB front;
    PxColorRGB back;

    pxb8 move_left  : 1;
    pxb8 move_right : 1;
    pxb8 move_up    : 1;
    pxb8 move_down  : 1;

}
PxConsoleGameState;

int
main(int argc, char** argv)
{
    #define PX_CONSOLE_FRAMES pxCast(pxiword, 2)

    PxArena arena = pxMemoryReserve(32);

    PxConsoleFrame frames[PX_CONSOLE_FRAMES] = {
        pxConsoleFrameMake(&arena, 50, 15),
        pxConsoleFrameMake(&arena, 50, 15),
        // pxConsoleFrameMake(&arena, 50, 15),
        // pxConsoleFrameMake(&arena, 50, 15),
    };

    pxiword frame = 0;

    PxConsole console = pxConsoleCreate(&arena);
    PxReader  reader  = pxConsoleReader(console, &arena, PX_MEMORY_KIB);
    PxWriter  writer  = pxConsoleWriter(console, &arena, 16 * PX_MEMORY_KIB);

    pxConsoleSetMode(console, PX_CONSOLE_MODE_MESSAGE);

    PxConsoleGameState game = {0};

    pxConsoleWriteCommand(&writer, pxConsoleCmdReset());
    pxConsoleWriteCommand(&writer, pxConsoleCmdCursorHide());
    pxWriterFlush(&writer);

    pxb8 active = 1;

    PxClock clock   = pxClockCreate(&arena);
    pxf32   elasped = 0;

    while (active != 0) {
        elasped += pxClockElapsed(clock);

        PxConsoleMsg message = pxConsolePollMessage(&reader);

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

        for (; elasped > 0.0167; elasped -= 0.0167) {
            pxu8 x = game.x + game.move_right - game.move_left;
            pxu8 y = game.y + game.move_down  - game.move_up;

            if (x >= 0 && x < frames[frame].width)  game.x = x;
            if (y >= 0 && y < frames[frame].height) game.y = y;

            game.back.r = (game.back.r + 1) % 256;
            game.back.g = (game.back.g + 2) % 256;
            game.back.b = (game.back.b + 3) % 256;

            pxConsoleFrameReset(&frames[frame], 0, game.front, game.back);

            pxConsoleFramePaint(&frames[frame], game.x, game.y,
                PX_ASCII_SHARP, game.front, game.back);

            pxConsoleWriteFrame(&writer, &frames[frame]);
            pxWriterFlush(&writer);

            frame = (frame + 1) % PX_CONSOLE_FRAMES;
        }
    }

    pxConsoleWriteCommand(&writer, pxConsoleCmdReset());
    pxWriterFlush(&writer);

    pxConsoleSetMode(console, PX_CONSOLE_MODE_DEFAULT);
}
