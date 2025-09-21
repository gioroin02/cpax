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

PxConsoleEscSeqnc
pxConsoleEscSeqncFromConsoleMsg(PxConsoleMsg value)
{
    PxConsoleEscSeqnc result = {0};

    switch (value.type) {
        case PX_CONSOLE_MSG_STYLE_TEXT_8: {
            result = pxConsoleEscSeqncMake((PxConsoleEscGroup[]) {
                pxConsoleEscGroupMake((pxuword[]) {30 + value.style_8.index}, 1)
            }, 1);

            result.func  = PX_ASCII_LOWER_M;
            result.flags = PX_CONSOLE_ESC_FLAG_CSI;
        } break;

        case PX_CONSOLE_MSG_STYLE_TEXT_256: {
            result = pxConsoleEscSeqncMake((PxConsoleEscGroup[]) {
                pxConsoleEscGroupMake((pxuword[]) {38}, 1),
                pxConsoleEscGroupMake((pxuword[]) {5}, 1),
                pxConsoleEscGroupMake((pxuword[]) {value.style_256.index}, 1),
            }, 3);

            result.func  = PX_ASCII_LOWER_M;
            result.flags = PX_CONSOLE_ESC_FLAG_CSI;
        } break;

        case PX_CONSOLE_MSG_STYLE_TEXT_RGB: {
            result = pxConsoleEscSeqncMake((PxConsoleEscGroup[]) {
                pxConsoleEscGroupMake((pxuword[]) {38}, 1),
                pxConsoleEscGroupMake((pxuword[]) {2}, 1),
                pxConsoleEscGroupMake((pxuword[]) {value.style_rgb.r}, 1),
                pxConsoleEscGroupMake((pxuword[]) {value.style_rgb.g}, 1),
                pxConsoleEscGroupMake((pxuword[]) {value.style_rgb.b}, 1),
            }, 5);

            result.func  = PX_ASCII_LOWER_M;
            result.flags = PX_CONSOLE_ESC_FLAG_CSI;
        } break;

        case PX_CONSOLE_MSG_STYLE_BACK_8: {
            result = pxConsoleEscSeqncMake((PxConsoleEscGroup[]) {
                pxConsoleEscGroupMake((pxuword[]) {40 + value.style_8.index}, 1)
            }, 1);

            result.func  = PX_ASCII_LOWER_M;
            result.flags = PX_CONSOLE_ESC_FLAG_CSI;
        } break;

        case PX_CONSOLE_MSG_STYLE_BACK_256: {
            result = pxConsoleEscSeqncMake((PxConsoleEscGroup[]) {
                pxConsoleEscGroupMake((pxuword[]) {48}, 1),
                pxConsoleEscGroupMake((pxuword[]) {5}, 1),
                pxConsoleEscGroupMake((pxuword[]) {value.style_256.index}, 1),
            }, 3);

            result.func  = PX_ASCII_LOWER_M;
            result.flags = PX_CONSOLE_ESC_FLAG_CSI;
        } break;

        case PX_CONSOLE_MSG_STYLE_BACK_RGB: {
            result = pxConsoleEscSeqncMake((PxConsoleEscGroup[]) {
                pxConsoleEscGroupMake((pxuword[]) {48}, 1),
                pxConsoleEscGroupMake((pxuword[]) {2}, 1),
                pxConsoleEscGroupMake((pxuword[]) {value.style_rgb.r}, 1),
                pxConsoleEscGroupMake((pxuword[]) {value.style_rgb.g}, 1),
                pxConsoleEscGroupMake((pxuword[]) {value.style_rgb.b}, 1),
            }, 5);

            result.func  = PX_ASCII_LOWER_M;
            result.flags = PX_CONSOLE_ESC_FLAG_CSI;
        } break;

        case PX_CONSOLE_MSG_STYLE_CLEAR: {
            result = pxConsoleEscSeqncMake((PxConsoleEscGroup[]) {
                pxConsoleEscGroupMake((pxuword[]) {0}, 1),
            }, 1);

            result.func  = PX_ASCII_LOWER_M;
            result.flags = PX_CONSOLE_ESC_FLAG_CSI;
        } break;

        case PX_CONSOLE_MSG_CURSOR_SHOW: {
            result = pxConsoleEscSeqncMake((PxConsoleEscGroup[]) {
                pxConsoleEscGroupMake((pxuword[]) {25}, 1),
            }, 1);

            result.func  = PX_ASCII_LOWER_H;
            result.flags = PX_CONSOLE_ESC_FLAG_CSI | PX_CONSOLE_ESC_FLAG_PRIV;
        } break;

        case PX_CONSOLE_MSG_CURSOR_HIDE: {
            result = pxConsoleEscSeqncMake((PxConsoleEscGroup[]) {
                pxConsoleEscGroupMake((pxuword[]) {25}, 1),
            }, 1);

            result.func  = PX_ASCII_LOWER_L;
            result.flags = PX_CONSOLE_ESC_FLAG_CSI | PX_CONSOLE_ESC_FLAG_PRIV;
        } break;

        case PX_CONSOLE_MSG_CURSOR_MOVE: {
            result = pxConsoleEscSeqncMake((PxConsoleEscGroup[]) {
                pxConsoleEscGroupMake((pxuword[]) {value.cursor_move.y + 1}, 1),
                pxConsoleEscGroupMake((pxuword[]) {value.cursor_move.x + 1}, 1),
            }, 2);

            result.func  = PX_ASCII_UPPER_H;
            result.flags = PX_CONSOLE_ESC_FLAG_CSI;
        } break;

        case PX_CONSOLE_MSG_CURSOR_MOVE_UP: {
            result.func  = PX_ASCII_UPPER_A;
            result.flags = PX_CONSOLE_ESC_FLAG_CSI;

            if (value.cursor_move.y > 0) {
                PxConsoleEscGroup group =
                    pxConsoleEscGroupMake((pxuword[]) {value.cursor_move.y}, 1);

                pxConsoleEscSeqncInsert(&result, group);
            }
        } break;

        case PX_CONSOLE_MSG_CURSOR_MOVE_DOWN: {
            result.func  = PX_ASCII_UPPER_B;
            result.flags = PX_CONSOLE_ESC_FLAG_CSI;

            if (value.cursor_move.y > 0) {
                PxConsoleEscGroup group =
                    pxConsoleEscGroupMake((pxuword[]) {value.cursor_move.y}, 1);

                pxConsoleEscSeqncInsert(&result, group);
            }
        } break;

        case PX_CONSOLE_MSG_CURSOR_MOVE_RIGHT: {
            result.func  = PX_ASCII_UPPER_C;
            result.flags = PX_CONSOLE_ESC_FLAG_CSI;

            if (value.cursor_move.x > 0) {
                PxConsoleEscGroup group =
                    pxConsoleEscGroupMake((pxuword[]) {value.cursor_move.x}, 1);

                pxConsoleEscSeqncInsert(&result, group);
            }
        } break;

        case PX_CONSOLE_MSG_CURSOR_MOVE_LEFT: {
            result.func  = PX_ASCII_UPPER_A;
            result.flags = PX_CONSOLE_ESC_FLAG_CSI;

            if (value.cursor_move.x > 0) {
                PxConsoleEscGroup group =
                    pxConsoleEscGroupMake((pxuword[]) {value.cursor_move.x}, 1);

                pxConsoleEscSeqncInsert(&result, group);
            }
        } break;

        case PX_CONSOLE_MSG_RESET: {
            result.func = PX_ASCII_LOWER_C;
        } break;

        default: break;
    }

    return result;
}

PxConsoleMsg
pxConsoleMsgFromConsoleEscSeqnc(PxConsoleEscSeqnc value)
{
    PxConsoleMsg result = {0};

    switch (value.func) {
        case PX_ASCII_LOWER_M: {

        } break;

        case PX_ASCII_UPPER_A: {
            result = pxConsoleMsgCursorMoveUp(1);

            if (value.size >= 1)
                result.cursor_move.y = value.items[0].items[0];
        } break;

        case PX_ASCII_UPPER_B: {
            result = pxConsoleMsgCursorMoveDown(1);

            if (value.size >= 1)
                result.cursor_move.y = value.items[0].items[0];
        } break;

        case PX_ASCII_UPPER_C: {
            result = pxConsoleMsgCursorMoveRight(1);

            if (value.size >= 1)
                result.cursor_move.x = value.items[0].items[0];
        } break;

        case PX_ASCII_UPPER_D: {
            result = pxConsoleMsgCursorMoveLeft(1);

            if (value.size >= 1)
                result.cursor_move.x = value.items[0].items[0];
        } break;

        case PX_ASCII_UPPER_H: {
            result = pxConsoleMsgCursorMove(0, 0);

            if (value.size >= 2) {
                result.cursor_move.x = value.items[1].items[0];
                result.cursor_move.y = value.items[0].items[0];
            }
        };

        default: break;
    }

    return result;
}

pxb8
pxConsoleQueueWriteMsg(PxConsoleQueue* self, PxConsoleMsg value)
{
    switch (value.type) {
        case PX_CONSOLE_MSG_STRING_8: {
            pxBuffer8WriteString8Tail(&self->buffer, value.string_8);
        } break;

        case PX_CONSOLE_MSG_STRING_16:{
            pxBuffer8WriteString16Tail(&self->buffer, value.string_16);
        } break;

        case PX_CONSOLE_MSG_STRING_32:{
            pxBuffer8WriteString32Tail(&self->buffer, value.string_32);
        } break;

        case PX_CONSOLE_MSG_UNICODE: {
            pxBuffer8WriteUnicodeTail(&self->buffer, value.unicode);
        } break;

        default: {
            PxConsoleEscSeqnc escape = pxConsoleEscSeqncFromConsoleMsg(value);

            PxFormatRadix radix = PX_FORMAT_RADIX_10;
            PxFormatFlag  flags = PX_FORMAT_FLAG_NONE;

            pxBuffer8WriteString8Tail(&self->buffer, pxs8("\x1b"));

            if ((escape.flags & PX_CONSOLE_ESC_FLAG_CSI) != 0)
                pxBuffer8WriteString8Tail(&self->buffer, pxs8("["));

            if ((escape.flags & PX_CONSOLE_ESC_FLAG_PRIV) != 0)
                pxBuffer8WriteString8Tail(&self->buffer, pxs8("?"));

            for (pxiword j = 0; j < escape.size; j += 1) {
                PxConsoleEscGroup* group = &escape.items[j];

                for (pxiword i = 0; i < group->size; i += 1) {
                    pxBuffer8WriteUnsignedTail(&self->buffer, group->items[i], radix, flags);

                    if (i + 1 < group->size)
                        pxBuffer8WriteString8Tail(&self->buffer, pxs8(":"));
                }

                if (j + 1 < escape.size)
                    pxBuffer8WriteString8Tail(&self->buffer, pxs8(";"));
            }

            pxBuffer8WriteUnicodeTail(&self->buffer, escape.func);
        } break;
    }

    return 1;
}

pxb8
pxConsoleQueueWriteList(PxConsoleQueue* self, PxConsoleMsg* values, pxiword length)
{
    PxBuffer8* buffer = &self->buffer;
    pxiword    size   = buffer->size;
    pxb8       state  = 0;

    for (pxiword i = 0; i < length; i += 1) {
        state =
            pxConsoleQueueWriteMsg(self, values[i]);

        if (state == 0) break;
    }

    if (state == 0)
        pxBuffer8DropTail(buffer, buffer->size - size);

    return state;
}

pxb8
pxConsoleQueueReadMsg(PxConsoleQueue* self, PxArena* arena, PxConsoleMsg* value)
{
    PxConsoleMsg result = {0};
    PxBuffer8*   buffer = &self->buffer;

    pxu8 byte = 0;

    if (pxBuffer8ReadMemory8Head(buffer, &byte, 1) == 0) return 0;

    if (byte != PX_ASCII_ESCAPE) {
        pxBuffer8DropHead(buffer, 1);

        if (value != 0)
            *value = pxConsoleMsgUnicode(byte);

        return 1;
    }

    byte = pxBuffer8GetForwOr(buffer, 1, 0);

    switch (byte) {
        case PX_ASCII_SQUARE_LEFT: {
            for (pxiword i = 2; i < buffer->size; i += 1) {
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
                        PxConsoleEscSeqnc escape = {0};

                        PxString8 string =
                            pxBuffer8ReadString8Head(buffer, arena, i + 1);

                        pxConsoleEscSeqncFromString8(string, &escape);

                        if (value != 0)
                            pxConsoleMsgFromConsoleEscSeqnc(escape);

                        return 1;
                    } break;

                    default: break;
                }
            }
        } break;
    }

    return 0;
}

pxb8
pxReaderConsoleQueue(PxReader* self, PxConsoleQueue* value)
{
    pxiword size =
        pxReaderBuffer8(self, &value->buffer, 0, 0);

    return size != 0 ? 1 : 0;
}

pxb8
pxWriterConsoleQueue(PxWriter* self, PxConsoleQueue* value)
{
    pxiword size =
        pxWriterBuffer8(self, &value->buffer);

    return size != 0 ? 1 : 0;
}

#endif // PX_CORE_CONSOLE_MESSAGE_C
