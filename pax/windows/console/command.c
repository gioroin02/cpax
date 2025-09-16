#ifndef PX_WINDOWS_CONSOLE_COMMAND_C
#define PX_WINDOWS_CONSOLE_COMMAND_C

#include "command.h"

void
pxWindowsConsoleWriteCmd(PxWriter* self, PxArena* arena, PxConsoleCmd value)
{
    switch (value.type) {
        case PX_CONSOLE_CMD_STYLE_8_FRONT: {
            pxWriterFormatVargs(self, arena, "\x1b[3${0}m",
                pxFormatCmdUnsigned(value.style_8, 10, 0));
        } break;

        case PX_CONSOLE_CMD_STYLE_8_BACK: {
            pxWriterFormatVargs(self, arena, "\x1b[4${0}m",
                pxFormatCmdUnsigned(value.style_8, 10, 0));
        } break;

        case PX_CONSOLE_CMD_STYLE_256_FRONT: {
            pxWriterFormatVargs(self, arena, "\x1b[38;5;${0}m",
                pxFormatCmdUnsigned(value.style_256, 10, 0));
        } break;

        case PX_CONSOLE_CMD_STYLE_256_BACK: {
            pxWriterFormatVargs(self, arena, "\x1b[48;5;${0}m",
                pxFormatCmdUnsigned(value.style_256, 10, 0));
        } break;

        case PX_CONSOLE_CMD_STYLE_RGB_FRONT: {
            pxWriterFormatVargs(self, arena, "\x1b[38;2;${0};${1};${2}m",
                pxFormatCmdUnsigned(value.style_rgb.r, 10, 0),
                pxFormatCmdUnsigned(value.style_rgb.g, 10, 0),
                pxFormatCmdUnsigned(value.style_rgb.b, 10, 0));
        } break;

        case PX_CONSOLE_CMD_STYLE_RGB_BACK: {
            pxWriterFormatVargs(self, arena, "\x1b[48;2;${0};${1};${2}m",
                pxFormatCmdUnsigned(value.style_rgb.r, 10, 0),
                pxFormatCmdUnsigned(value.style_rgb.g, 10, 0),
                pxFormatCmdUnsigned(value.style_rgb.b, 10, 0));
        } break;

        case PX_CONSOLE_CMD_STYLE_CLEAR:
            pxWriterFormatVargs(self, arena, "\x1b[0m", {0});
        break;

        case PX_CONSOLE_CMD_CURSOR_SHOW:
            pxWriterFormatVargs(self, arena, "\x1b[?25h", {0});
        break;

        case PX_CONSOLE_CMD_CURSOR_HIDE:
            pxWriterFormatVargs(self, arena, "\x1b[?25l", {0});
        break;

        case PX_CONSOLE_CMD_CURSOR_UP: {
            pxWriterFormatVargs(self, arena, "\x1b[${0}A",
                pxFormatCmdUnsigned(value.cursor_move, 10, 0));
        } break;

        case PX_CONSOLE_CMD_CURSOR_DOWN: {
            pxWriterFormatVargs(self, arena, "\x1b[${0}B",
                pxFormatCmdUnsigned(value.cursor_move, 10, 0));
        } break;

        case PX_CONSOLE_CMD_CURSOR_RIGHT: {
            pxWriterFormatVargs(self, arena, "\x1b[${0}C",
                pxFormatCmdUnsigned(value.cursor_move, 10, 0));
        } break;

        case PX_CONSOLE_CMD_CURSOR_LEFT: {
            pxWriterFormatVargs(self, arena, "\x1b[${0}D",
                pxFormatCmdUnsigned(value.cursor_move, 10, 0));
        } break;

        case PX_CONSOLE_CMD_CURSOR_PLACE: {
            pxWriterFormatVargs(self, arena, "\x1b[${0};${1}H",
                pxFormatCmdUnsigned(value.cursor_place.x + 1, 10, 0),
                pxFormatCmdUnsigned(value.cursor_place.y + 1, 10, 0));
        } break;

        case PX_CONSOLE_CMD_UNICODE:
            pxWriterUnicode(self, arena, value.unicode);
        break;

        case PX_CONSOLE_CMD_STRING_8:
            pxWriterString8(self, value.string_8);
        break;

        case PX_CONSOLE_CMD_STRING_16:
            pxWriterString16(self, value.string_16);
        break;

        case PX_CONSOLE_CMD_STRING_32:
            pxWriterString32(self, value.string_32);
        break;

        case PX_CONSOLE_CMD_RESET:
            pxWriterString8(self, pxs8("\x1b\x63"));
        break;

        default: break;
    }
}

#endif // PX_WINDOWS_CONSOLE_COMMAND_C
