#include "../export.h"

#include "../../time/export.h"
#include "../../structure/export.h"

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

    pxb8 dirty;
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

    self->dirty = 0;

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

    self->dirty = 1;

    return pxConsoleFrameUpdate(self, x, y, item);
}

pxiword
pxWriterFormatConsoleCmd(PxWriter self, PxArena* arena, PxConsoleCmd value)
{
    pxiword result = 0;

    switch (value.type) {
        case PX_CONSOLE_CMD_STYLE_8_FRONT: {
            result = pxWriterFormatVargs(self, arena, "\x1b[3${0}m",
                pxFormatCmdUnsigned(value.style_8, 10, 0));
        } break;

        case PX_CONSOLE_CMD_STYLE_8_BACK: {
            result = pxWriterFormatVargs(self, arena, "\x1b[4${0}m",
                pxFormatCmdUnsigned(value.style_8, 10, 0));
        } break;

        case PX_CONSOLE_CMD_STYLE_256_FRONT: {
            result = pxWriterFormatVargs(self, arena, "\x1b[38;5;${0}m",
                pxFormatCmdUnsigned(value.style_256, 10, 0));
        } break;

        case PX_CONSOLE_CMD_STYLE_256_BACK: {
            result = pxWriterFormatVargs(self, arena, "\x1b[48;5;${0}m",
                pxFormatCmdUnsigned(value.style_256, 10, 0));
        } break;

        case PX_CONSOLE_CMD_STYLE_RGB_FRONT: {
            result = pxWriterFormatVargs(self, arena, "\x1b[38;2;${0};${1};${2}m",
                pxFormatCmdUnsigned(value.style_rgb.r, 10, 0),
                pxFormatCmdUnsigned(value.style_rgb.g, 10, 0),
                pxFormatCmdUnsigned(value.style_rgb.b, 10, 0));
        } break;

        case PX_CONSOLE_CMD_STYLE_RGB_BACK: {
            result = pxWriterFormatVargs(self, arena, "\x1b[48;2;${0};${1};${2}m",
                pxFormatCmdUnsigned(value.style_rgb.r, 10, 0),
                pxFormatCmdUnsigned(value.style_rgb.g, 10, 0),
                pxFormatCmdUnsigned(value.style_rgb.b, 10, 0));
        } break;

        case PX_CONSOLE_CMD_STYLE_CLEAR:
            result = pxWriterFormatVargs(self, arena, "\x1b[0m", {0});
        break;

        case PX_CONSOLE_CMD_CURSOR_SHOW:
            result = pxWriterFormatVargs(self, arena, "\x1b[?25h", {0});
        break;

        case PX_CONSOLE_CMD_CURSOR_HIDE:
            result = pxWriterFormatVargs(self, arena, "\x1b[?25l", {0});
        break;

        case PX_CONSOLE_CMD_CURSOR_UP: {
            result = pxWriterFormatVargs(self, arena, "\x1b[${0}A",
                pxFormatCmdUnsigned(value.cursor_move, 10, 0));
        } break;

        case PX_CONSOLE_CMD_CURSOR_DOWN: {
            result = pxWriterFormatVargs(self, arena, "\x1b[${0}B",
                pxFormatCmdUnsigned(value.cursor_move, 10, 0));
        } break;

        case PX_CONSOLE_CMD_CURSOR_RIGHT: {
            result = pxWriterFormatVargs(self, arena, "\x1b[${0}C",
                pxFormatCmdUnsigned(value.cursor_move, 10, 0));
        } break;

        case PX_CONSOLE_CMD_CURSOR_LEFT: {
            result = pxWriterFormatVargs(self, arena, "\x1b[${0}D",
                pxFormatCmdUnsigned(value.cursor_move, 10, 0));
        } break;

        case PX_CONSOLE_CMD_CURSOR_PLACE: {
            result = pxWriterFormatVargs(self, arena, "\x1b[${0};${1}H",
                pxFormatCmdUnsigned(value.cursor_place.x + 1, 10, 0),
                pxFormatCmdUnsigned(value.cursor_place.y + 1, 10, 0));
        } break;

        case PX_CONSOLE_CMD_UNICODE:
            result = pxWriterUnicode(self, arena, value.unicode);
        break;

        case PX_CONSOLE_CMD_STRING_8:
            result = pxWriterString8(self, value.string_8);
        break;

        case PX_CONSOLE_CMD_STRING_16:
            result = pxWriterString16(self, value.string_16);
        break;

        case PX_CONSOLE_CMD_STRING_32:
            result = pxWriterString32(self, value.string_32);
        break;

        case PX_CONSOLE_CMD_RESET:
            result = pxWriterString8(self, pxs8("\x1b\x63"));
        break;

        default: break;
    }

    return result;
}

void
pxWriterFormatConsoleFrame(PxWriter self, PxArena* arena, PxConsoleFrame* frame)
{
    PxConsoleCell item = pxConsoleFrameReadOr(frame, 0, 0, (PxConsoleCell) {0});

    PxColorRGB front = item.front;
    PxColorRGB back  = item.back;

    pxWriterFormatConsoleCmd(self, arena, pxConsoleCmdCursorPlace(0, 0));
    pxWriterFormatConsoleCmd(self, arena, pxConsoleCmdStyleRGBFront(front.r, front.g, front.b));
    pxWriterFormatConsoleCmd(self, arena, pxConsoleCmdStyleRGBBack(back.r, back.g, back.b));

    for (pxiword j = 0; j < frame->height; j += 1) {
        for (pxiword i = 0; i < frame->width; i += 1) {
            item = pxConsoleFrameReadOr(frame, i, j, (PxConsoleCell) {0});

            if (pxColorRGBIsEqual(&front, &item.front) == 0) {
                front = item.front;

                pxWriterFormatConsoleCmd(self, arena,
                    pxConsoleCmdStyleRGBFront(front.r, front.g, front.b));
            }

            if (pxColorRGBIsEqual(&back, &item.back) == 0) {
                back = item.back;

                pxWriterFormatConsoleCmd(self, arena,
                    pxConsoleCmdStyleRGBBack(back.r, back.g, back.b));
            }

            pxWriterFormatConsoleCmd(self, arena,
                pxConsoleCmdUnicode(item.unicode));
        }

        pxWriterFormatConsoleCmd(self, arena,
            pxConsoleCmdCursorPlace(0, j + 1));
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
    PxArena arena = pxMemoryReserve(32);

    PxConsole console = pxConsoleCreate(&arena);
    PxReader  reader  = pxReaderFromConsole(console, &arena, PX_MEMORY_KIB);
    PxWriter  writer  = pxConsoleWriter(console, &arena, PX_MEMORY_KIB);

    PxConsoleMsg message = {0};

    PxConsoleFrame frame   = pxConsoleFrameMake(&arena, 30, 10);
    PxBuffer8      command = pxBuffer8Reserve(&arena, PX_MEMORY_KIB);

    PxWriter painter = pxBufferWriter(&command, &arena, PX_MEMORY_KIB);

    pxConsoleSetMode(console, PX_CONSOLE_MODE_MESSAGE);

    GameState game = {
        .front = {.r = 128, .g = 128, .b = 128},
    };

    pxWriterFormatConsoleCmd(writer, &arena, pxConsoleCmdReset());
    pxWriterFormatConsoleCmd(writer, &arena, pxConsoleCmdCursorHide());

    pxWriterFlush(writer);

    pxb8 active = 1;

    PxClock clock = pxClockCreate(&arena);

    pxf32 slice   = 1.0 / 64.0;
    pxf32 elapsed = 0;

    for (pxiword i = 0; active != 0; i += 1) {
        elapsed += pxClockElapsed(clock);

        do {
            message = pxConsolePollMsg(reader, &arena);

            switch (message.type) {
                case PX_CONSOLE_MSG_KEYBD_PRESS: {
                    if (message.keybd_button.button == PX_CONSOLE_KEYBD_ESCAPE)
                        active = 0;

                    switch (message.keybd_button.button) {
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
                    switch (message.keybd_button.button) {
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

            if (x >= 0 && x < frame_list[frame].width)  game.x = x;
            if (y >= 0 && y < frame_list[frame].height) game.y = y;

            pxf32 comp_r = (1 + sin(i * 0.0001 + 3)) * 128;
            pxf32 comp_g = (1 + sin(i * 0.0001 + 5)) * 128;
            pxf32 comp_b = (1 + sin(i * 0.0001 + 7)) * 128;

            game.back.r = pxas(pxu8, pxbetween(comp_r, 0, 256));
            game.back.g = pxas(pxu8, pxbetween(comp_g, 0, 256));
            game.back.b = pxas(pxu8, pxbetween(comp_b, 0, 256));

            pxConsoleFrameReset(&frame_list[frame], 0, game.front, game.back);

            pxConsoleFramePaint(&frame_list[frame], game.x, game.y,
                PX_ASCII_SHARP, (PxColorRGB) {0}, game.back);

            if (pxConsoleFrameIsDirty(&frame_list[frame]) != 0)
                pxConsoleWriteFrame(writer, &arena, &frame_list[frame]);

            pxWriterFlush(writer);

            elapsed -= slice;
            frame    = (frame + 1) % frame_size;
        }
    }

    pxWriterFormatConsoleCmd(writer, &arena, pxConsoleCmdReset());

    pxWriterFlush(writer);

    pxConsoleSetMode(console, PX_CONSOLE_MODE_DEFAULT);
}
