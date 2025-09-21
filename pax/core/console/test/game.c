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
pxColorRGBIsEqual(PxColorRGB self, PxColorRGB value)
{
    return pxMemoryIsEqual(self.items, value.items, 3, 1);
}

typedef struct PxConsoleValue
{
    pxi32      unicode;
    PxColorRGB text;
    PxColorRGB back;
}
PxConsoleValue;

typedef struct PxConsoleBatch
{
    PxArray items;

    pxiword width;
    pxiword height;
    pxb8    dirty;
}
PxConsoleBatch;

PxConsoleBatch
pxConsoleBatchReserve(PxArena* arena, pxiword width, pxiword height)
{
    PxConsoleBatch result = {0};

    if (width <= 0 || height <= 0) return result;

    result.items = pxArrayReserve(arena,
        PxConsoleValue, width * height);

    if (result.items.length > 0) {
        pxArrayFill(&result.items);

        result.width  = width;
        result.height = height;
    }

    return result;
}

pxb8
pxConsoleBatchIsDirty(PxConsoleBatch* self)
{
    return self->dirty != 0 ? 1 : 0;
}

pxb8
pxConsoleBatchRead(PxConsoleBatch* self, pxiword x, pxiword y, PxConsoleValue* value)
{
    if (x < 0 || x >= self->width)  return 0;
    if (y < 0 || y >= self->height) return 0;

    pxiword index = x + self->width * y;

    return pxArrayRead(&self->items,
        index, PxConsoleValue, value);
}

PxConsoleValue
pxConsoleBatchReadOr(PxConsoleBatch* self, pxiword x, pxiword y, PxConsoleValue value)
{
    PxConsoleValue result = {0};

    if (pxConsoleBatchRead(self, x, y, &result) == 0)
        return value;

    return result;
}

pxb8
pxConsoleBatchUpdate(PxConsoleBatch* self, pxiword x, pxiword y, PxConsoleValue value)
{
    if (x < 0 || x >= self->width)  return 0;
    if (y < 0 || y >= self->height) return 0;

    pxiword index = x + self->width * y;

    return pxArrayUpdate(&self->items,
        index, PxConsoleValue, &value);
}

pxb8
pxConsoleBatchReset(PxConsoleBatch* self, pxi32 unicode, PxColorRGB text, PxColorRGB back)
{
    if (unicode < 32) unicode = 32;

    PxConsoleValue item = {
        .unicode = unicode,
        .text   = text,
        .back    = back,
    };

    for (pxiword j = 0; j < self->height; j += 1) {
        for (pxiword i = 0; i < self->width; i += 1) {
            if (pxConsoleBatchUpdate(self, i, j, item) == 0)
                return 0;
        }
    }

    self->dirty = 0;

    return 1;
}

pxb8
pxConsoleBatchPaint(PxConsoleBatch* self, pxiword x, pxiword y, pxi32 unicode, PxColorRGB text, PxColorRGB back)
{
    if (unicode < 32) unicode = 32;

    PxConsoleValue item = {
        .unicode = unicode,
        .text   = text,
        .back    = back,
    };

    self->dirty = 1;

    return pxConsoleBatchUpdate(self, x, y, item);
}

void
pxConsoleQueueWriteBatch(PxConsoleQueue* self, PxConsoleBatch* batch)
{
    PxConsoleValue item = pxConsoleBatchReadOr(batch, 0, 0, (PxConsoleValue) {0});

    PxColorRGB text = item.text;
    PxColorRGB back = item.back;

    pxConsoleQueueWriteMsg(self, pxConsoleMsgCursorMove(0, 0));
    pxConsoleQueueWriteMsg(self, pxConsoleMsgStyleTextRGB(text.r, text.g, text.b));
    pxConsoleQueueWriteMsg(self, pxConsoleMsgStyleBackRGB(back.r, back.g, back.b));

    for (pxiword j = 0; j < batch->height; j += 1) {
        for (pxiword i = 0; i < batch->width; i += 1) {
            item = pxConsoleBatchReadOr(batch, i, j, (PxConsoleValue) {0});

            if (pxColorRGBIsEqual(text, item.text) == 0) {
                text = item.text;

                pxConsoleQueueWriteMsg(self,
                    pxConsoleMsgStyleTextRGB(text.r, text.g, text.b));
            }

            if (pxColorRGBIsEqual(back, item.back) == 0) {
                back = item.back;

                pxConsoleQueueWriteMsg(self,
                    pxConsoleMsgStyleBackRGB(back.r, back.g, back.b));
            }

            pxConsoleQueueWriteMsg(self,
                pxConsoleMsgUnicode(item.unicode));
        }

        pxConsoleQueueWriteMsg(self,
            pxConsoleMsgCursorMove(0, j + 1));
    }
}

typedef struct Game
{
    pxu8 x, y;

    PxColorRGB text;
    PxColorRGB back;

    pxb8 move_left  : 1;
    pxb8 move_right : 1;
    pxb8 move_up    : 1;
    pxb8 move_down  : 1;
}
Game;

int
main(int argc, char** argv)
{
    PxArena arena = pxMemoryReserve(32);

    PxConsole console = pxConsoleCreate(&arena);

    PxReader reader = pxReaderFromInput(
        pxInputFromConsole(console), &arena, PX_MEMORY_KIB);

    PxWriter writer = pxWriterFromOutput(
        pxOutputFromConsole(console), &arena, PX_MEMORY_KIB);

    PxConsoleMsg   message = {0};
    PxConsoleBatch batch   = pxConsoleBatchReserve(&arena, 200, 40);

    PxConsoleQueue input  = pxConsoleQueueReserve(&arena, PX_MEMORY_KIB);
    PxConsoleQueue output = pxConsoleQueueReserve(&arena, PX_MEMORY_KIB * 16);

    pxConsoleSetMode(console, PX_CONSOLE_MODE_MESSAGE);

    Game game = {
        .text = {.r = 128, .g = 128, .b = 128},
    };

    pxConsoleQueueWriteMsg(&output, pxConsoleMsgReset());
    pxConsoleQueueWriteMsg(&output, pxConsoleMsgCursorHide());

    pxWriterConsoleQueue(&writer, &output);
    pxWriterFlush(&writer);

    pxb8 active = 1;

    PxClock clock = pxClockCreate(&arena);

    pxf32 slice   = 1.0 / 144.0;
    pxf32 elapsed = 0;

    for (pxiword i = 0; active != 0; i += 1) {
        elapsed += pxClockElapsed(clock);

        // pxReaderConsoleQueue(&reader, &input);

        while (pxConsoleQueueReadMsg(&input, &arena, &message) != 0) {
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

            if (x >= 0 && x < batch.width)  game.x = x;
            if (y >= 0 && y < batch.height) game.y = y;

            pxf32 comp_r = pxbetween((1 + sin(i * slice + 3)) * 128, 1, 255);
            pxf32 comp_g = pxbetween((1 + sin(i * slice + 5)) * 128, 1, 255);
            pxf32 comp_b = pxbetween((1 + sin(i * slice + 7)) * 128, 1, 255);

            game.back.r = pxas(pxu8, comp_r);
            game.back.g = pxas(pxu8, comp_g);
            game.back.b = pxas(pxu8, comp_b);

            pxConsoleBatchReset(&batch, 0, game.text, game.back);

            pxConsoleBatchPaint(&batch, game.x, game.y,
                PX_ASCII_SHARP, (PxColorRGB) {0}, game.back);

            if (pxConsoleBatchIsDirty(&batch) != 0)
                pxConsoleQueueWriteBatch(&output, &batch);

            pxWriterConsoleQueue(&writer, &output);
            pxWriterFlush(&writer);

            elapsed = 0;
        }
    }

    pxConsoleQueueWriteMsg(&output, pxConsoleMsgReset());

    pxWriterConsoleQueue(&writer, &output);
    pxWriterFlush(&writer);

    pxConsoleSetMode(console, PX_CONSOLE_MODE_DEFAULT);
}
