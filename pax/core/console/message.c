#ifndef PX_CORE_CONSOLE_MESSAGE_C
#define PX_CORE_CONSOLE_MESSAGE_C

#include "message.h"

PxConsoleMsg
pxConsoleMsgKeybdPress(pxiword button, pxuword modifs, pxi32 unicode)
{
    return (PxConsoleMsg) {
        .type = PX_CONSOLE_MSG_KEYBD_PRESS,

        .keybd_button = {
            .button  = button,
            .modifs  = modifs,
            .unicode = unicode,
        },
    };
}

PxConsoleMsg
pxConsoleMsgKeybdRelease(pxiword button, pxuword modifs, pxi32 unicode)
{
    return (PxConsoleMsg) {
        .type = PX_CONSOLE_MSG_KEYBD_RELEASE,

        .keybd_button = {
            .button  = button,
            .modifs  = modifs,
            .unicode = unicode,
        },
    };
}

PxConsoleMsg
pxConsoleMsgStyleText8(pxu8 index)
{
    return (PxConsoleMsg) {
        .type = PX_CONSOLE_MSG_STYLE_TEXT_8,

        .style_8 = {
            .index = index,
        },
    };
}

PxConsoleMsg
pxConsoleMsgStyleText256(pxu8 index)
{
    return (PxConsoleMsg) {
        .type = PX_CONSOLE_MSG_STYLE_TEXT_256,

        .style_256 = {
            .index = index,
        },
    };
}

PxConsoleMsg
pxConsoleMsgStyleTextRGB(pxu8 r, pxu8 g, pxu8 b)
{
    return (PxConsoleMsg) {
        .type = PX_CONSOLE_MSG_STYLE_TEXT_RGB,

        .style_rgb = {
            .r = r,
            .g = g,
            .b = b,
        },
    };
}

PxConsoleMsg
pxConsoleMsgStyleBack8(pxu8 index)
{
    return (PxConsoleMsg) {
        .type = PX_CONSOLE_MSG_STYLE_BACK_8,

        .style_8 = {
            .index = index,
        },
    };
}

PxConsoleMsg
pxConsoleMsgStyleBack256(pxu8 index)
{
    return (PxConsoleMsg) {
        .type = PX_CONSOLE_MSG_STYLE_BACK_256,

        .style_256 = {
            .index = index,
        },
    };
}

PxConsoleMsg
pxConsoleMsgStyleBackRGB(pxu8 r, pxu8 g, pxu8 b)
{
    return (PxConsoleMsg) {
        .type = PX_CONSOLE_MSG_STYLE_BACK_RGB,

        .style_rgb = {
            .r = r,
            .g = g,
            .b = b,
        },
    };
}

PxConsoleMsg
pxConsoleMsgStyleClear()
{
    return (PxConsoleMsg) {
        .type = PX_CONSOLE_MSG_STYLE_CLEAR,
    };
}

PxConsoleMsg
pxConsoleMsgString8(PxString8 value)
{
    return (PxConsoleMsg) {
        .type     = PX_CONSOLE_MSG_STRING_8,
        .string_8 = value,
    };
}

PxConsoleMsg
pxConsoleMsgString16(PxString16 value)
{
    return (PxConsoleMsg) {
        .type      = PX_CONSOLE_MSG_STRING_16,
        .string_16 = value,
    };
}

PxConsoleMsg
pxConsoleMsgString32(PxString32 value)
{
    return (PxConsoleMsg) {
        .type      = PX_CONSOLE_MSG_STRING_32,
        .string_32 = value,
    };
}

PxConsoleMsg
pxConsoleMsgUnicode(pxi32 value)
{
    return (PxConsoleMsg) {
        .type    = PX_CONSOLE_MSG_UNICODE,
        .unicode = value,
    };
}

PxConsoleMsg
pxConsoleMsgCursorShow()
{
    return (PxConsoleMsg) {
        .type = PX_CONSOLE_MSG_CURSOR_SHOW,
    };
}

PxConsoleMsg
pxConsoleMsgCursorHide()
{
    return (PxConsoleMsg) {
        .type = PX_CONSOLE_MSG_CURSOR_HIDE,
    };
}

PxConsoleMsg
pxConsoleMsgCursorMove(pxiword x, pxiword y)
{
    return (PxConsoleMsg) {
        .type = PX_CONSOLE_MSG_CURSOR_MOVE,

        .cursor_move = {
            .x = x,
            .y = y,
        },
    };
}

PxConsoleMsg
pxConsoleMsgCursorMoveUp(pxiword y)
{
    return (PxConsoleMsg) {
        .type = PX_CONSOLE_MSG_CURSOR_MOVE_UP,

        .cursor_move = {
            .x = 0,
            .y = y,
        },
    };
}

PxConsoleMsg
pxConsoleMsgCursorMoveDown(pxiword y)
{
    return (PxConsoleMsg) {
        .type = PX_CONSOLE_MSG_CURSOR_MOVE_DOWN,

        .cursor_move = {
            .x = 0,
            .y = y,
        },
    };
}

PxConsoleMsg
pxConsoleMsgCursorMoveLeft(pxiword x)
{
    return (PxConsoleMsg) {
        .type = PX_CONSOLE_MSG_CURSOR_MOVE_LEFT,

        .cursor_move = {
            .x = x,
            .y = 0,
        },
    };
}

PxConsoleMsg
pxConsoleMsgCursorMoveRight(pxiword x)
{
    return (PxConsoleMsg) {
        .type = PX_CONSOLE_MSG_CURSOR_MOVE_RIGHT,

        .cursor_move = {
            .x = x,
            .y = 0,
        },
    };
}

PxConsoleMsg
pxConsoleMsgReset()
{
    return (PxConsoleMsg) {
        .type = PX_CONSOLE_MSG_RESET,
    };
}

PxConsoleQueue
pxConsoleQueueReserve(PxArena* arena, pxiword length)
{
    PxConsoleQueue result = {0};

    result.buffer = pxBuffer8Reserve(arena, length);

    return result;
}

pxb8
pxConsoleMsgFromString8(PxString8 string, PxConsoleMsg* value)
{
    PxAnsiSequence sequence = {0};

    return 1;
}

pxb8
pxConsoleQueueWriteMsg(PxConsoleQueue* self, PxArena* arena, PxConsoleMsg value)
{
    switch (value.type) {
        case PX_CONSOLE_MSG_STYLE_TEXT_8: {
            pxu8 format[] = "\x1b[3${0}m";

            return pxBuffer8PrintVargs(&self->buffer, format,
                pxPrintCmdUnsigned(value.style_8.index));
        } break;

        case PX_CONSOLE_MSG_STYLE_TEXT_256: {
            pxu8 format[] = "\x1b[38;5;${0}m";

            return pxBuffer8PrintVargs(&self->buffer, format,
                pxPrintCmdUnsigned(value.style_256.index));
        } break;

        case PX_CONSOLE_MSG_STYLE_TEXT_RGB: {
            pxu8 format[] = "\x1b[38;2;${0};${1};${2}m";

            return pxBuffer8PrintVargs(&self->buffer, format,
                pxPrintCmdUnsigned(value.style_rgb.r),
                pxPrintCmdUnsigned(value.style_rgb.g),
                pxPrintCmdUnsigned(value.style_rgb.b));
        } break;

        case PX_CONSOLE_MSG_STYLE_BACK_8: {
            pxu8 format[] = "\x1b[4${0}m";

            return pxBuffer8PrintVargs(&self->buffer, format,
                pxPrintCmdUnsigned(value.style_8.index));
        } break;

        case PX_CONSOLE_MSG_STYLE_BACK_256: {
            pxu8 format[] = "\x1b[48;5;${0}m";

            return pxBuffer8PrintVargs(&self->buffer, format,
                pxPrintCmdUnsigned(value.style_256.index));
        } break;

        case PX_CONSOLE_MSG_STYLE_BACK_RGB: {
            pxu8 format[] = "\x1b[48;2;${0};${1};${2}m";

            return pxBuffer8PrintVargs(&self->buffer, format,
                pxPrintCmdUnsigned(value.style_rgb.r),
                pxPrintCmdUnsigned(value.style_rgb.g),
                pxPrintCmdUnsigned(value.style_rgb.b));
        } break;

        case PX_CONSOLE_MSG_STYLE_CLEAR: {
            return pxBuffer8PrintVargs(&self->buffer, "\x1b[0m", {0});
        } break;

        case PX_CONSOLE_MSG_STRING_8: {
            return pxBuffer8PrintVargs(&self->buffer, "${0}",
                pxPrintCmdString8(value.string_8));
        } break;

        case PX_CONSOLE_MSG_STRING_16: {
            return pxBuffer8PrintVargs(&self->buffer, "${0}",
                pxPrintCmdString16(value.string_16));
        } break;

        case PX_CONSOLE_MSG_STRING_32: {
            return pxBuffer8PrintVargs(&self->buffer, "${0}",
                pxPrintCmdString32(value.string_32));
        } break;

        case PX_CONSOLE_MSG_UNICODE: {
            return pxBuffer8PrintVargs(&self->buffer, "${0}",
                pxPrintCmdUnicode(value.unicode));
        } break;

        case PX_CONSOLE_MSG_CURSOR_SHOW: {
            return pxBuffer8PrintVargs(&self->buffer, "\x1b[?25h", {0});
        } break;

        case PX_CONSOLE_MSG_CURSOR_HIDE: {
            return pxBuffer8PrintVargs(&self->buffer, "\x1b[?25l", {0});
        } break;

        case PX_CONSOLE_MSG_CURSOR_MOVE: {
            if (value.cursor_move.x <= 0 && value.cursor_move.y <= 0)
                return 1;

            pxu8 format[] = "\x1b[${0};${1}H";

            return pxBuffer8PrintVargs(&self->buffer, format,
                pxPrintCmdUnsigned(value.cursor_move.y + 1),
                pxPrintCmdUnsigned(value.cursor_move.x + 1));
        } break;

        case PX_CONSOLE_MSG_CURSOR_MOVE_UP: {
            if (value.cursor_move.y <= 0) return 1;

            pxu8 format[] = "\x1b[${0}A";

            return pxBuffer8PrintVargs(&self->buffer, format,
                pxPrintCmdUnsigned(value.cursor_move.y));
        } break;

        case PX_CONSOLE_MSG_CURSOR_MOVE_DOWN: {
            if (value.cursor_move.y <= 0) return 1;

            pxu8 format[] = "\x1b[${0}B";

            return pxBuffer8PrintVargs(&self->buffer, format,
                pxPrintCmdUnsigned(value.cursor_move.y));
        } break;

        case PX_CONSOLE_MSG_CURSOR_MOVE_RIGHT: {
            if (value.cursor_move.x <= 0) return 1;

            pxu8 format[] = "\x1b[${0}C";

            return pxBuffer8PrintVargs(&self->buffer, format,
                pxPrintCmdUnsigned(value.cursor_move.x));
        } break;

        case PX_CONSOLE_MSG_CURSOR_MOVE_LEFT: {
            if (value.cursor_move.x <= 0) return 1;

            pxu8 format[] = "\x1b[${0}D";

            return pxBuffer8PrintVargs(&self->buffer, format,
                pxPrintCmdUnsigned(value.cursor_move.x));
        } break;

        case PX_CONSOLE_MSG_RESET: {
            return pxBuffer8PrintVargs(&self->buffer, "\x1b\x63", {0});
        } break;

        default: break;
    }

    return 1;
}

pxb8
pxConsoleQueueWriteList(PxConsoleQueue* self, PxArena* arena, PxConsoleMsg* values, pxiword length)
{
    PxBuffer8* buffer = &self->buffer;
    pxiword    size   = buffer->size;
    pxb8       state  = 0;

    for (pxiword i = 0; i < length; i += 1) {
        state = pxConsoleQueueWriteMsg(self,
            arena, values[i]);

        if (state == 0) break;
    }

    if (state == 0)
        pxBuffer8DropTail(buffer, buffer->size - size);

    return state;
}

PxConsoleMsg
pxConsoleQueueReadMsg(PxConsoleQueue* self, PxArena* arena)
{
    PxConsoleMsg result = {0};

    PxBuffer8* buffer = &self->buffer;
    pxu8       byte   = pxBuffer8GetForwOr(buffer, 0, 0);

    if (byte != PX_ASCII_ESCAPE) {
        pxBuffer8DropHead(buffer, 1);

        return pxConsoleMsgUnicode(byte);
    }

    for (pxiword i = 1; i < buffer->size; i += 1) {
        pxu8 byte = pxBuffer8GetForwOr(buffer, i, 0);

        switch (byte) {
            case PX_ASCII_TILDE:
            case PX_ASCII_UPPER_A:
            case PX_ASCII_UPPER_B:
            case PX_ASCII_UPPER_C:
            case PX_ASCII_UPPER_D:
            case PX_ASCII_UPPER_F:
            case PX_ASCII_UPPER_H:
            case PX_ASCII_LOWER_H:
            case PX_ASCII_LOWER_L:
            case PX_ASCII_LOWER_M:
            case PX_ASCII_LOWER_U: {
                PxString8 string = pxBuffer8ReadString8Head(
                    buffer, arena, i + 1);

                if (pxConsoleMsgFromString8(string, &result) != 0)
                    return result;
            } break;

            default: break;
        }
    }

    return result;
}

#endif // PX_CORE_CONSOLE_MESSAGE_C
