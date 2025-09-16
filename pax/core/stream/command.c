#ifndef PX_CORE_STREAM_COMMAND_C
#define PX_CORE_STREAM_COMMAND_C

#include "command.h"

PxString8
pxString8MatchFormatSpec(PxString8 string)
{
    pxu8*   memory = string.memory;
    pxiword length = string.length;
    pxiword index  = 0;

    if (memory == 0 || length <= 2) return (PxString8) {0};

    if (memory[index] != PX_ASCII_BRACE_LEFT)
        return (PxString8) {0};

    for (index += 1; memory[index] != PX_ASCII_BRACE_RIGHT;) {
        if (index + 1 >= length)
            return (PxString8) {0};

        index += 1;
    }

    return pxString8Make(memory + 1, index - 1);
}

PxFormatCmd
pxFormatCmdString8(PxString8 value)
{
    return (PxFormatCmd) {
        .type     = PX_FORMAT_CMD_STRING_8,
        .string_8 = value,
    };
}

PxFormatCmd
pxFormatCmdString16(PxString16 value)
{
    return (PxFormatCmd) {
        .type      = PX_FORMAT_CMD_STRING_16,
        .string_16 = value,
    };
}

PxFormatCmd
pxFormatCmdString32(PxString32 value)
{
    return (PxFormatCmd) {
        .type      = PX_FORMAT_CMD_STRING_32,
        .string_32 = value,
    };
}

PxFormatCmd
pxFormatCmdUnicode(pxi32 value)
{
    return (PxFormatCmd) {
        .type    = PX_FORMAT_CMD_UNICODE,
        .unicode = value,
    };
}

PxFormatCmd
pxFormatCmdUnsigned(pxuword value, PxFormatRadix radix, PxFormatFlag flags)
{
    return (PxFormatCmd) {
        .type = PX_FORMAT_CMD_UNSIGNED,

        .unsigned_word = {
            .value = value,
            .radix = radix,
            .flags = flags,
        },
    };
}

PxFormatCmd
pxFormatCmdInteger(pxiword value, PxFormatRadix radix, PxFormatFlag flags)
{
    return (PxFormatCmd) {
        .type = PX_FORMAT_CMD_INTEGER,

        .integer_word = {
            .value = value,
            .radix = radix,
            .flags = flags,
        },
    };
}

PxFormatCmd
pxFormatCmdFloating(pxfword value, PxFormatRadix radix, PxFormatFlag flags)
{
    return (PxFormatCmd) {
        .type = PX_FORMAT_CMD_FLOATING,

        .floating_word = {
            .value = value,
            .radix = radix,
            .flags = flags,
        },
    };
}

PxFormatCmd
pxFormatCmdBoolean(pxbword value, PxFormatFlag flags)
{
    return (PxFormatCmd) {
        .type = PX_FORMAT_CMD_BOOLEAN,

        .boolean_word = {
            .value = value,
            .flags = flags,
        },
    };
}

PxFormatCmd
pxFormatCmdDelegate(void* ctxt, void* proc)
{
    return (PxFormatCmd) {
        .type = PX_FORMAT_CMD_DELEGATE,

        .delegate = {
            .ctxt = ctxt,
            .proc = proc,
        },
    };
}

pxiword
pxWriterFormatCmd(PxWriter* self, PxArena* arena, PxFormatCmd value)
{
    pxiword offset = pxArenaOffset(arena);
    pxiword result = 0;

    switch (value.type) {
        case PX_FORMAT_CMD_STRING_8:
            result = pxWriterString8(self, value.string_8);
        break;

        case PX_FORMAT_CMD_STRING_16:
            result = pxWriterString16(self, value.string_16);
        break;

        case PX_FORMAT_CMD_STRING_32:
            result = pxWriterString32(self, value.string_32);
        break;

        case PX_FORMAT_CMD_UNICODE:
            result = pxWriterUnicode(self, arena, value.unicode);
        break;

        case PX_FORMAT_CMD_UNSIGNED: {
            PxFormatRadix radix = value.unsigned_word.radix;
            PxFormatFlag  flags = value.unsigned_word.flags;

            PxString8 string = pxString8FromUnsigned(arena,
                value.unsigned_word.value, radix, flags);

            result = pxWriterString8(self, string);
        } break;

        case PX_FORMAT_CMD_INTEGER: {
            PxFormatRadix radix = value.integer_word.radix;
            PxFormatFlag  flags = value.integer_word.flags;

            PxString8 string = pxString8FromInteger(arena,
                value.integer_word.value, radix, flags);

            result = pxWriterString8(self, string);
        } break;

        case PX_FORMAT_CMD_FLOATING: {
            PxFormatRadix radix = value.floating_word.radix;
            PxFormatFlag  flags = value.floating_word.flags;

            PxString8 string = {0}; /* pxString8FromFloating(arena,
                value.floating_word.value, radix, flags); */

            result = pxWriterString8(self, string);
        } break;

        case PX_FORMAT_CMD_BOOLEAN: {
            PxFormatFlag flags = value.boolean_word.flags;

            PxString8 string = pxString8FromBoolean(arena,
                value.boolean_word.value, flags);

            result = pxWriterString8(self, string);
        } break;

        case PX_FORMAT_CMD_DELEGATE: {
            void* proc = value.delegate.proc;

            result = pxas(PxWriterFormatProc*, proc)
                (self, value.delegate.ctxt);
        } break;

        default: break;
    }

    pxArenaRewind(arena, offset);

    return result;
}

pxiword
pxWriterFormatList(PxWriter* self, PxArena* arena, pxiword start, pxiword stop, PxFormatCmd* list)
{
    pxiword result = 0;

    for (pxiword i = start; i < stop; i += 1)
        result += pxWriterFormatCmd(self, arena, list[i]);

    return result;
}

pxiword
pxWriterFormat(PxWriter* self, PxArena* arena, PxString8 format, pxiword start, pxiword stop, PxFormatCmd* list)
{
    pxiword result = 0;
    pxiword index  = 0;
    pxb8    state  = 0;

    pxiword requests = pxString8Contains(format, pxs8("$"));

    PxString8 left  = {0};
    PxString8 right = format;

    for (; requests > 0; requests -= 1) {
        pxString8Split(right, pxs8("$"), &left, &right);

        result += pxWriterFormatCmd(self, arena,
            pxFormatCmdString8(left));

        left  = pxString8MatchFormatSpec(right);
        right = pxString8SliceHead(right, left.length + 2);

        state = pxIntegerFromString8(left, &index,
            PX_FORMAT_RADIX_10, PX_FORMAT_FLAG_NONE);

        PxFormatCmd command = pxFormatCmdString8(pxs8("${?}"));

        if (state != 0 && index >= start && index < stop)
            command = list[index];

        result += pxWriterFormatCmd(self, arena, command);
    }

    result += pxWriterFormatCmd(self, arena,
        pxFormatCmdString8(right));

    return result;
}

#endif // PX_CORE_STREAM_COMMAND_C
