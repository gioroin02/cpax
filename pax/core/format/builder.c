#ifndef PX_CORE_FORMAT_BUILDER_C
#define PX_CORE_FORMAT_BUILDER_C

#include "builder.h"

PxString8
pxFormatSpecFromMemory8(pxu8* memory, pxiword length)
{
    pxiword index = 0;

    if (memory == 0 || length <= 2) return (PxString8) {0};

    if (memory[index] != PX_ASCII_BRACE_LEFT)
        return (PxString8) {0};

    for (index += 1; memory[index] != PX_ASCII_BRACE_RIGHT;) {
        if (index + 1 >= length)
            return (PxString8) {0};

        index += 1;
    }

    return (PxString8) {
        .memory = memory + 1,
        .length = index  - 1,
    };
}

PxBuilderCmd
pxBuilderCmdUnsigned8(pxuword radix, PxFormatOption options, pxu8 value)
{
    return (PxBuilderCmd) {
        .type = PX_BUILDER_CMD_UNSIGNED8,

        .cmd_u8 = {
            .radix   = radix,
            .options = options,
            .value   = value,
        },
    };
}

PxBuilderCmd
pxBuilderCmdUnsigned16(pxuword radix, PxFormatOption options, pxu16 value)
{
    return (PxBuilderCmd) {
        .type = PX_BUILDER_CMD_UNSIGNED16,

        .cmd_u16 = {
            .radix   = radix,
            .options = options,
            .value   = value,
        },
    };
}

PxBuilderCmd
pxBuilderCmdUnsigned32(pxuword radix, PxFormatOption options, pxu32 value)
{
    return (PxBuilderCmd) {
        .type = PX_BUILDER_CMD_UNSIGNED32,

        .cmd_u32 = {
            .radix   = radix,
            .options = options,
            .value   = value,
        },
    };
}

PxBuilderCmd
pxBuilderCmdUnsigned64(pxuword radix, PxFormatOption options, pxu64 value)
{
    return (PxBuilderCmd) {
        .type = PX_BUILDER_CMD_UNSIGNED64,

        .cmd_u64 = {
            .radix   = radix,
            .options = options,
            .value   = value,
        },
    };
}

PxBuilderCmd
pxBuilderCmdUnsigned(pxuword radix, PxFormatOption options, pxuword value)
{
    return (PxBuilderCmd) {
        .type = PX_BUILDER_CMD_UNSIGNED,

        .cmd_uword = {
            .radix   = radix,
            .options = options,
            .value   = value,
        },
    };
}

PxBuilderCmd
pxBuilderCmdInteger8(pxuword radix, PxFormatOption options, pxi8 value)
{
    return (PxBuilderCmd) {
        .type = PX_BUILDER_CMD_INTEGER8,

        .cmd_i8 = {
            .radix   = radix,
            .options = options,
            .value   = value,
        },
    };
}

PxBuilderCmd
pxBuilderCmdInteger16(pxuword radix, PxFormatOption options, pxi16 value)
{
    return (PxBuilderCmd) {
        .type = PX_BUILDER_CMD_INTEGER16,

        .cmd_i16 = {
            .radix   = radix,
            .options = options,
            .value   = value,
        },
    };
}

PxBuilderCmd
pxBuilderCmdInteger32(pxuword radix, PxFormatOption options, pxi32 value)
{
    return (PxBuilderCmd) {
        .type = PX_BUILDER_CMD_INTEGER32,

        .cmd_i32 = {
            .radix   = radix,
            .options = options,
            .value   = value,
        },
    };
}

PxBuilderCmd
pxBuilderCmdInteger64(pxuword radix, PxFormatOption options, pxi64 value)
{
    return (PxBuilderCmd) {
        .type = PX_BUILDER_CMD_INTEGER64,

        .cmd_i64 = {
            .radix   = radix,
            .options = options,
            .value   = value,
        },
    };
}

PxBuilderCmd
pxBuilderCmdInteger(pxuword radix, PxFormatOption options, pxiword value)
{
    return (PxBuilderCmd) {
        .type = PX_BUILDER_CMD_INTEGER,

        .cmd_iword = {
            .radix   = radix,
            .options = options,
            .value   = value,
        },
    };
}

PxBuilderCmd
pxBuilderCmdUnicode(pxi32 value)
{
    return (PxBuilderCmd) {
        .type    = PX_BUILDER_CMD_UNICODE,
        .cmd_uni = value,
    };
}

PxBuilderCmd
pxBuilderCmdString8(PxString8 value)
{
    return (PxBuilderCmd) {
        .type     = PX_BUILDER_CMD_STRING8,
        .cmd_str8 = value,
    };
}

PxBuilderCmd
pxBuilderCmdString16(PxString16 value)
{
    return (PxBuilderCmd) {
        .type      = PX_BUILDER_CMD_STRING16,
        .cmd_str16 = value,
    };
}

PxBuilderCmd
pxBuilderCmdString32(PxString32 value)
{
    return (PxBuilderCmd) {
        .type      = PX_BUILDER_CMD_STRING32,
        .cmd_str32 = value,
    };
}

PxBuilder
pxBuilderReserve(PxArena* arena, pxiword length)
{
    PxBuilder result = {0};

    if (length <= 0) return result;

    result.memory = pxArenaReserve(arena, pxu32, length);

    if (result.memory != 0)
        result.length = length;

    return result;
}

void
pxBuilderClear(PxBuilder* self)
{
    self->size = 0;
}

pxiword
pxBuilderFormat(PxBuilder* self, PxString8 format, pxiword start, pxiword stop, PxBuilderCmd* list)
{
    pxiword index  = 0;
    pxiword result = 0;
    pxiword temp   = 1;

    for (; index < format.length && temp != 0; result += temp) {
        PxBuilderCmd command = {0};
        pxi32        unicode = 0;

        index += pxUtf8ReadMemory8Forw(format.memory,
            format.length, index, &unicode);

        switch (unicode) {
            case PX_ASCII_DOLLAR: {
                pxiword value = 0;
                pxb8    state = 0;

                PxString8 spec = pxFormatSpecFromMemory8(
                    format.memory + index, format.length - index);

                state = pxIntegerFromString8(&value,
                    10, PX_FORMAT_OPTION_NONE, spec);

                if (value < start || value >= stop || state == 0)
                    command = pxBuilderCmdString8(pxs8("${?}"));
                else
                    command = list[value];

                index += spec.length + 2;
            } break;

            default:
                command = pxBuilderCmdUnicode(unicode);
            break;
        }

        temp = pxBuilderCommand(self, command);
    }

    return result;
}

pxiword
pxBuilderList(PxBuilder* self, pxiword start, pxiword stop, PxBuilderCmd* list)
{
    if (list == 0 || stop <= start) return 0;

    pxiword diff = stop - start;

    for (pxiword i = 0; i < diff; i += 1) {
        if (pxBuilderCommand(self, list[i + start]) == 0)
            return i;
    }

    return diff;
}

pxiword
pxBuilderCommand(PxBuilder* self, PxBuilderCmd command)
{
    pxu32*  memory = self->memory + self->size;
    pxiword size   = self->length - self->size;
    pxiword result = 0;

    switch (command.type) {
        case PX_BUILDER_CMD_UNSIGNED8: {
            PxBuilderCmdUnsigned8 cmd = command.cmd_u8;

            result = pxMemory32WriteUnsigned8(memory, size,
                cmd.radix, cmd.options, cmd.value);
        } break;

        case PX_BUILDER_CMD_UNSIGNED16: {
            PxBuilderCmdUnsigned16 cmd = command.cmd_u16;

            result = pxMemory32WriteUnsigned16(memory, size,
                cmd.radix, cmd.options, cmd.value);
        } break;

        case PX_BUILDER_CMD_UNSIGNED32: {
            PxBuilderCmdUnsigned32 cmd = command.cmd_u32;

            result = pxMemory32WriteUnsigned32(memory, size,
                cmd.radix, cmd.options, cmd.value);
        } break;

        case PX_BUILDER_CMD_UNSIGNED64: {
            PxBuilderCmdUnsigned64 cmd = command.cmd_u64;

            result = pxMemory32WriteUnsigned64(memory, size,
                cmd.radix, cmd.options, cmd.value);
        } break;

        case PX_BUILDER_CMD_UNSIGNED: {
            PxBuilderCmdUnsigned cmd = command.cmd_uword;

            result = pxMemory32WriteUnsigned(memory, size,
                cmd.radix, cmd.options, cmd.value);
        } break;

        case PX_BUILDER_CMD_INTEGER8: {
            PxBuilderCmdInteger8 cmd = command.cmd_i8;

            result = pxMemory32WriteInteger8(memory, size,
                cmd.radix, cmd.options, cmd.value);
        } break;

        case PX_BUILDER_CMD_INTEGER16: {
            PxBuilderCmdInteger16 cmd = command.cmd_i16;

            result = pxMemory32WriteInteger16(memory, size,
                cmd.radix, cmd.options, cmd.value);
        } break;

        case PX_BUILDER_CMD_INTEGER32: {
            PxBuilderCmdInteger32 cmd = command.cmd_i32;

            result = pxMemory32WriteInteger32(memory, size,
                cmd.radix, cmd.options, cmd.value);
        } break;

        case PX_BUILDER_CMD_INTEGER64: {
            PxBuilderCmdInteger64 cmd = command.cmd_i64;

            result = pxMemory32WriteInteger64(memory, size,
                cmd.radix, cmd.options, cmd.value);
        } break;

        case PX_BUILDER_CMD_INTEGER: {
            PxBuilderCmdInteger cmd = command.cmd_iword;

            result = pxMemory32WriteInteger(memory, size,
                cmd.radix, cmd.options, cmd.value);
        } break;

        case PX_BUILDER_CMD_UNICODE: {
            pxi32 cmd = command.cmd_uni;

            result = pxUtf32UnitsToWrite(cmd);

            if (result != 0)
                memory[0] = cmd;
        } break;

        case PX_BUILDER_CMD_STRING8: {
            PxString8 cmd = command.cmd_str8;

            pxiword length = pxUtf32UnitsFromMemory8(
                cmd.memory, cmd.length);

            if (length < 0 || length >= size) return 0;

            pxiword index = 0;
            pxiword other = 0;

            while (index < length) {
                pxi32 unicode = 0;

                other += pxUtf8ReadMemory8Forw(
                    cmd.memory, cmd.length, other, &unicode);

                index += pxUtf32WriteMemory32Forw(
                    memory, length, index, unicode);
            }

            result = length;
        } break;

        case PX_BUILDER_CMD_STRING16: {
            PxString16 cmd = command.cmd_str16;

            pxiword length = pxUtf32UnitsFromMemory16(
                cmd.memory, cmd.length);

            if (length < 0 || length >= size) return 0;

            pxiword index = 0;
            pxiword other = 0;

            while (index < length) {
                pxi32 unicode = 0;

                other += pxUtf16ReadMemory16Forw(
                    cmd.memory, cmd.length, other, &unicode);

                index += pxUtf32WriteMemory32Forw(
                    memory, length, index, unicode);
            }

            result = length;
        } break;

        case PX_BUILDER_CMD_STRING32: {
            PxString32 cmd = command.cmd_str32;

            if (cmd.length < 0 || cmd.length >= size)
                return 0;

            for (pxiword i = 0; i < cmd.length; i += 1)
                memory[i] = cmd.memory[i];

            result = cmd.length;
        } break;

        default: break;
    }

    self->size += result;

    return result;
}

PxString8
pxString8FromBuilder(PxArena* arena, PxBuilder* builder)
{
    PxString32 string = {
        .memory = builder->memory,
        .length = builder->size,
    };

    return pxString8CopyString32(arena, string);
}

PxString16
pxString16FromBuilder(PxArena* arena, PxBuilder* builder)
{
    PxString32 string = {
        .memory = builder->memory,
        .length = builder->size,
    };

    return pxString16CopyString32(arena, string);
}

PxString32
pxString32FromBuilder(PxArena* arena, PxBuilder* builder)
{
    PxString32 string = {
        .memory = builder->memory,
        .length = builder->size,
    };

    return pxString32Copy(arena, string);
}

#endif // PX_CORE_FORMAT_BUILDER_C
