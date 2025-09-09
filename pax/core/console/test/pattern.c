#include "../export.h"
#include "../../structure/export.h"

typedef struct PxConsoleKeybdState
{
    pxb8 move_left  : 1;
    pxb8 move_right : 1;
    pxb8 move_up    : 1;
    pxb8 move_down  : 1;

}
PxConsoleKeybdState;

typedef struct PxConsoleColor
{
    union {
        struct {
            pxu8 r;
            pxu8 g;
            pxu8 b;
        };

        pxu8 items[3];
    };
}
PxConsoleColor;

typedef struct PxConsoleCell
{
    pxi32          unicode;
    PxConsoleColor foreground;
    PxConsoleColor background;
}
PxConsoleCell;

typedef struct PxConsoleFrame
{
    PxArray items;

    pxiword width;
    pxiword height;
}
PxConsoleFrame;

typedef PxBuffer8 PxConsoleCommand;

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
pxConsoleFrameReset(PxConsoleFrame* self, pxi32 unicode, PxConsoleColor foreground, PxConsoleColor background)
{
    if (unicode < 32) unicode = 32;

    PxConsoleCell item = {
        .unicode    = unicode,
        .foreground = foreground,
        .background = background,
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
pxConsoleFramePaint(PxConsoleFrame* self, pxiword x, pxiword y, pxi32 unicode, PxConsoleColor foreground, PxConsoleColor background)
{
    if (unicode < 32) unicode = 32;

    PxConsoleCell item = {
        .unicode    = unicode,
        .foreground = foreground,
        .background = background,
    };

    return pxConsoleFrameUpdate(self, x, y, item);
}

PxConsoleCommand
pxConsoleCommandMake(PxArena* arena, pxiword length)
{
    return pxBuffer8Reserve(arena, length);
}

void
pxConsoleCommandClear(PxConsoleCommand* self)
{
    pxBuffer8Clear(self);
}

pxiword
pxConsoleCommandMoveUp(PxConsoleCommand* self, pxu8 amount)
{
    if (amount <= 0) return 0;

    pxBuffer8Normalize(self);

    pxiword s0 = pxBuffer8WriteString8Tail(self, pxs8("\033["));

    pxiword s1 = 0;

    if (amount > 1) {
        pxu8*   memory = self->memory + self->size;
        pxiword length = self->length - self->size;

        s1 = pxMemory8WriteUnsigned8(memory, length,
            10, PX_FORMAT_OPTION_NONE, amount);

        self->size += s1;
        self->tail  = (self->tail + s1) % self->length;
    }

    pxiword s2 = pxBuffer8WriteString8Tail(self, pxs8("A"));

    return s0 + s1 + s2;
}

pxiword
pxConsoleCommandMoveDown(PxConsoleCommand* self, pxu8 amount)
{
    if (amount <= 0) return 0;

    pxBuffer8Normalize(self);

    pxiword s0 = pxBuffer8WriteString8Tail(self, pxs8("\033["));

    pxiword s1 = 0;

    if (amount > 1) {
        pxu8*   memory = self->memory + self->size;
        pxiword length = self->length - self->size;

        s1 = pxMemory8WriteUnsigned8(memory, length,
            10, PX_FORMAT_OPTION_NONE, amount);

        self->size += s1;
        self->tail  = (self->tail + s1) % self->length;
    }

    pxiword s2 = pxBuffer8WriteString8Tail(self, pxs8("B"));

    return s0 + s1 + s2;
}

pxiword
pxConsoleCommandMoveLeft(PxConsoleCommand* self, pxu8 amount)
{
    if (amount <= 0) return 0;

    pxBuffer8Normalize(self);

    pxiword s0 = pxBuffer8WriteString8Tail(self, pxs8("\033["));

    pxiword s1 = 0;

    if (amount > 1) {
        pxu8*   memory = self->memory + self->size;
        pxiword length = self->length - self->size;

        s1 = pxMemory8WriteUnsigned8(memory, length,
            10, PX_FORMAT_OPTION_NONE, amount);

        self->size += s1;
        self->tail  = (self->tail + s1) % self->length;
    }

    pxiword s2 = pxBuffer8WriteString8Tail(self, pxs8("D"));

    return s0 + s1 + s2;
}

pxiword
pxConsoleCommandMoveRight(PxConsoleCommand* self, pxu8 amount)
{
    if (amount <= 0) return 0;

    pxBuffer8Normalize(self);

    pxiword s0 = pxBuffer8WriteString8Tail(self, pxs8("\033["));

    pxiword s1 = 0;

    if (amount > 1) {
        pxu8*   memory = self->memory + self->size;
        pxiword length = self->length - self->size;

        s1 = pxMemory8WriteUnsigned8(memory, length,
            10, PX_FORMAT_OPTION_NONE, amount);

        self->size += s1;
        self->tail  = (self->tail + s1) % self->length;
    }

    pxiword s2 = pxBuffer8WriteString8Tail(self, pxs8("C"));

    return s0 + s1 + s2;
}

pxiword
pxConsoleCommandMoveTo(PxConsoleCommand* self, pxiword x, pxiword y)
{
    if (x < 0 || y < 0) return 0;

    pxiword s0 = pxBuffer8WriteString8Tail(self, pxs8("\033["));

    pxBuffer8Normalize(self);

    pxiword s1 = 0;
    pxiword s2 = 0;
    pxiword s3 = 0;

    if (x != 0 || y != 0) {
        pxu8*   memory = self->memory + self->size;
        pxiword length = self->length - self->size;

        s1 = pxMemory8WriteUnsigned8(memory, length,
            10, PX_FORMAT_OPTION_NONE, y + 1);

        self->size += s1;
        self->tail  = (self->tail + s1) % self->length;

        s2 = pxBuffer8WriteString8Tail(self, pxs8(";"));

        memory = self->memory + self->size;
        length = self->length - self->size;

        s3 = pxMemory8WriteUnsigned8(memory, length,
            10, PX_FORMAT_OPTION_NONE, x + 1);

        self->size += s3;
        self->tail  = (self->tail + s3) % self->length;
    }

    pxiword s4 = pxBuffer8WriteString8Tail(self, pxs8("H"));

    return s0 + s1 + s2 + s3 + s4;
}

pxiword
pxConsoleCommandShowCursor(PxConsoleCommand* self, pxb8 state)
{
    PxString8 string = pxs8("\033[?25l");

    if (state != 0)
        string = pxs8("\033[?25h");

    return pxBuffer8WriteString8Tail(self, string);
}

pxiword
pxConsoleCommandRefresh(PxConsoleCommand* self, pxb8 scroll)
{
    PxString8 string = pxs8("\033c");

    if (scroll != 0)
        string = pxs8("\033[2J");

    return pxBuffer8WriteString8Tail(self, string);
}

pxiword
pxConsoleCommandForeground(PxConsoleCommand* self, PxConsoleColor color)
{
    pxiword s0 = pxBuffer8WriteString8Tail(self, pxs8("\033[38;2;"));

    pxBuffer8Normalize(self);

    pxu8*   memory = self->memory + self->size;
    pxiword length = self->length - self->size;

    pxiword s1 = pxMemory8WriteUnsigned8(memory, length,
        10, PX_FORMAT_OPTION_NONE, color.r);

    self->size += s1;
    self->tail  = (self->tail + s1) % self->length;

    pxiword s2 = pxBuffer8WriteString8Tail(self, pxs8(";"));

    memory = self->memory + self->size;
    length = self->length - self->size;

    pxiword s3 = pxMemory8WriteUnsigned8(memory, length,
        10, PX_FORMAT_OPTION_NONE, color.g);

    self->size += s3;
    self->tail  = (self->tail + s3) % self->length;

    pxiword s4 = pxBuffer8WriteString8Tail(self, pxs8(";"));

    memory = self->memory + self->size;
    length = self->length - self->size;

    pxiword s5 = pxMemory8WriteUnsigned8(memory, length,
        10, PX_FORMAT_OPTION_NONE, color.b);

    self->size += s5;
    self->tail  = (self->tail + s5) % self->length;

    pxiword s6 = pxBuffer8WriteString8Tail(self, pxs8("m"));

    return s0 + s1 + s2;
}

pxiword
pxConsoleCommandBackground(PxConsoleCommand* self, PxConsoleColor color)
{
    pxiword s0 = pxBuffer8WriteString8Tail(self, pxs8("\033[48;2;"));

    pxBuffer8Normalize(self);

    pxu8*   memory = self->memory + self->size;
    pxiword length = self->length - self->size;

    pxiword s1 = pxMemory8WriteUnsigned8(memory, length,
        10, PX_FORMAT_OPTION_NONE, color.r);

    self->size += s1;
    self->tail  = (self->tail + s1) % self->length;

    pxiword s2 = pxBuffer8WriteString8Tail(self, pxs8(";"));

    memory = self->memory + self->size;
    length = self->length - self->size;

    pxiword s3 = pxMemory8WriteUnsigned8(memory, length,
        10, PX_FORMAT_OPTION_NONE, color.g);

    self->size += s3;
    self->tail  = (self->tail + s3) % self->length;

    pxiword s4 = pxBuffer8WriteString8Tail(self, pxs8(";"));

    memory = self->memory + self->size;
    length = self->length - self->size;

    pxiword s5 = pxMemory8WriteUnsigned8(memory, length,
        10, PX_FORMAT_OPTION_NONE, color.b);

    self->size += s5;
    self->tail  = (self->tail + s5) % self->length;

    pxiword s6 = pxBuffer8WriteString8Tail(self, pxs8("m"));

    return s0 + s1 + s2;
}

pxiword
pxConsoleCommandUnicode(PxConsoleCommand* self, pxi32 value)
{
    pxBuffer8Normalize(self);

    pxu8* memory = self->memory + self->size;
    pxu8  length = self->length - self->size;

    pxiword size = pxUtf8WriteMemory8Forw(memory, length, 0, value);

    if (size <= 0) return 0;

    self->size += size;
    self->tail  = (self->tail + size) % self->length;

    return size;
}

void
pxConsoleCommandFrame(PxConsoleCommand* self, PxConsoleFrame* frame)
{
    for (pxiword j = 0; j < frame->height; j += 1) {
        for (pxiword i = 0; i < frame->width; i += 1) {
            PxConsoleCell item = pxConsoleFrameReadOr(frame,
                i, j, (PxConsoleCell) {0});

            pxConsoleCommandMoveTo(self, i, j);

            pxConsoleCommandForeground(self, item.foreground);
            pxConsoleCommandBackground(self, item.background);

            pxConsoleCommandUnicode(self, item.unicode);
        }
    }
}

pxb8
pxConsoleWriteCommand(PxConsole self, PxConsoleCommand* command)
{
    if (pxConsoleWrite(self, command) != 0)
        return 1;

    return 0;
}

#define FRAMES 2

int
main(int argc, char** argv)
{
    PxArena arena = pxMemoryReserve(16);

    PxConsoleCommand command =
        pxConsoleCommandMake(&arena, 4 * PX_MEMORY_KIB);


    PxConsoleFrame frames[FRAMES] = {
        pxConsoleFrameMake(&arena, 25, 5),
        pxConsoleFrameMake(&arena, 25, 5),
    };

    pxiword frame = 0;

    pxu8 x = 1;
    pxu8 y = 1;

    PxConsoleColor foreground = {0};
    PxConsoleColor background = {0};

    PxConsole console = pxConsoleCreate(&arena, PX_MEMORY_KIB);

    pxConsoleInputModeRaw(console);

    PxConsoleKeybdState keybd = {0};

    pxConsoleCommandRefresh(&command, 0);
    pxConsoleCommandShowCursor(&command, 0);

    pxConsoleWriteCommand(console, &command);

    pxb8 active = 1;

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
            x = pxClamp(x + dx, 1, frames[frame].width);
            y = pxClamp(y + dy, 1, frames[frame].height);
        }

        foreground.r = (foreground.r + 1) % 256;
        foreground.g = (foreground.g + 2) % 256;
        foreground.b = (foreground.b + 3) % 256;

        background.r = (background.r + 1) % 256;
        background.g = (background.g + 2) % 256;
        background.b = (background.b + 3) % 256;

        pxConsoleFrameReset(&frames[frame], PX_ASCII_SPACE,
            (PxConsoleColor) {0}, background);

        pxConsoleFramePaint(&frames[frame], x - 1, y - 1,
            PX_ASCII_SHARP, (PxConsoleColor) {0}, background);

        if (i % 1000 == 0) {
            pxConsoleCommandFrame(&command, &frames[frame]);
            pxConsoleWriteCommand(console, &command);

            frame = (frame + 1) % FRAMES;
        }
    }

    pxConsoleCommandRefresh(&command, 0);
    pxConsoleWriteCommand(console, &command);

    pxConsoleInputModeRestore(console);
}
