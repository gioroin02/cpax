#ifndef PX_CORE_FORMAT_BUILDER_C
#define PX_CORE_FORMAT_BUILDER_C

#include "builder.h"

PxString8
pxFormatSpecFromString8(PxString8 string)
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

PxBuilderCmd
pxBuilderCmdUnsigned8(pxuword radix, PxFormatOption options, pxu8 value)
{
    return (PxBuilderCmd) {
        .type = PX_BUILDER_CMD_UNSIGNED_8,

        .unsigned_8 = {
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
        .type = PX_BUILDER_CMD_UNSIGNED_16,

        .unsigned_16 = {
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
        .type = PX_BUILDER_CMD_UNSIGNED_32,

        .unsigned_32 = {
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
        .type = PX_BUILDER_CMD_UNSIGNED_64,

        .unsigned_64 = {
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

        .unsigned_word = {
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
        .type = PX_BUILDER_CMD_INTEGER_8,

        .integer_8 = {
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
        .type = PX_BUILDER_CMD_INTEGER_16,

        .integer_16 = {
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
        .type = PX_BUILDER_CMD_INTEGER_32,

        .integer_32 = {
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
        .type = PX_BUILDER_CMD_INTEGER_64,

        .integer_64 = {
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

        .integer_word = {
            .radix   = radix,
            .options = options,
            .value   = value,
        },
    };
}

PxBuilderCmd
pxBuilderCmdBoolean8(pxb8 value)
{
    return (PxBuilderCmd) {
        .type      = PX_BUILDER_CMD_BOOLEAN_8,
        .boolean_8 = value,
    };
}

PxBuilderCmd
pxBuilderCmdBoolean16(pxb16 value)
{
    return (PxBuilderCmd) {
        .type      = PX_BUILDER_CMD_BOOLEAN_16,
        .boolean_16 = value,
    };
}

PxBuilderCmd
pxBuilderCmdBoolean32(pxb32 value)
{
    return (PxBuilderCmd) {
        .type       = PX_BUILDER_CMD_BOOLEAN_32,
        .boolean_32 = value,
    };
}

PxBuilderCmd
pxBuilderCmdBoolean64(pxb64 value)
{
    return (PxBuilderCmd) {
        .type       = PX_BUILDER_CMD_BOOLEAN_64,
        .boolean_64 = value,
    };
}

PxBuilderCmd
pxBuilderCmdBoolean(pxbword value)
{
    return (PxBuilderCmd) {
        .type         = PX_BUILDER_CMD_BOOLEAN,
        .boolean_word = value,
    };
}

PxBuilderCmd
pxBuilderCmdUnicode(pxi32 value)
{
    return (PxBuilderCmd) {
        .type    = PX_BUILDER_CMD_UNICODE,
        .unicode = value,
    };
}

PxBuilderCmd
pxBuilderCmdString8(PxString8 value)
{
    return (PxBuilderCmd) {
        .type     = PX_BUILDER_CMD_STRING_8,
        .string_8 = value,
    };
}

PxBuilderCmd
pxBuilderCmdString16(PxString16 value)
{
    return (PxBuilderCmd) {
        .type      = PX_BUILDER_CMD_STRING_16,
        .string_16 = value,
    };
}

PxBuilderCmd
pxBuilderCmdString32(PxString32 value)
{
    return (PxBuilderCmd) {
        .type      = PX_BUILDER_CMD_STRING_32,
        .string_32 = value,
    };
}

PxBuilderCmd
pxBuilderCmdDelegate(void* ctxt, void* proc)
{
    return (PxBuilderCmd) {
        .type = PX_BUILDER_CMD_DELEGATE,

        .delegate = {
            .ctxt = ctxt,
            .proc = proc,
        },
    };
}

PxBuilder
pxBuilderMake(pxu8* memory, pxiword length)
{
    PxBuilder result = {0};

    if (memory != 0 && length > 0) {
        result.memory = memory;
        result.length = length;
    }

    return result;
}

PxBuilder
pxBuilderReserve(PxArena* arena, pxiword length)
{
    pxu8* memory =
        pxArenaReserve(arena, pxu8, length);

    return pxBuilderMake(memory, length);
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

    while (index < format.length) {
        PxBuilderCmd command = {0};
        pxi32        unicode = 0;

        index += pxUtf8ReadMemory8Forw(
            format.memory, format.length, index, &unicode);

        switch (unicode) {
            case PX_ASCII_DOLLAR: {
                pxiword value = 0;
                pxb8    state = 0;

                PxString8 spec = pxFormatSpecFromString8(
                    pxString8SliceHead(format, index));

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

        result += pxBuilderCommand(self, command);
    }

    return result;
}

pxiword
pxBuilderChain(PxBuilder* self, pxiword start, pxiword stop, PxBuilderCmd* list)
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
    pxu8*   memory = self->memory + self->size;
    pxiword size   = self->length - self->size;
    pxiword result = 0;

    switch (command.type) {
        case PX_BUILDER_CMD_UNSIGNED_8: {
            PxBuilderCmdUnsigned8 cmd = command.unsigned_8;

            result = pxMemory8WriteUnsigned8(memory, size,
                cmd.radix, cmd.options, cmd.value);
        } break;

        case PX_BUILDER_CMD_UNSIGNED_16: {
            PxBuilderCmdUnsigned16 cmd = command.unsigned_16;

            result = pxMemory8WriteUnsigned16(memory, size,
                cmd.radix, cmd.options, cmd.value);
        } break;

        case PX_BUILDER_CMD_UNSIGNED_32: {
            PxBuilderCmdUnsigned32 cmd = command.unsigned_32;

            result = pxMemory8WriteUnsigned32(memory, size,
                cmd.radix, cmd.options, cmd.value);
        } break;

        case PX_BUILDER_CMD_UNSIGNED_64: {
            PxBuilderCmdUnsigned64 cmd = command.unsigned_64;

            result = pxMemory8WriteUnsigned64(memory, size,
                cmd.radix, cmd.options, cmd.value);
        } break;

        case PX_BUILDER_CMD_UNSIGNED: {
            PxBuilderCmdUnsigned cmd = command.unsigned_word;

            result = pxMemory8WriteUnsigned(memory, size,
                cmd.radix, cmd.options, cmd.value);
        } break;

        case PX_BUILDER_CMD_INTEGER_8: {
            PxBuilderCmdInteger8 cmd = command.integer_8;

            result = pxMemory8WriteInteger8(memory, size,
                cmd.radix, cmd.options, cmd.value);
        } break;

        case PX_BUILDER_CMD_INTEGER_16: {
            PxBuilderCmdInteger16 cmd = command.integer_16;

            result = pxMemory8WriteInteger16(memory, size,
                cmd.radix, cmd.options, cmd.value);
        } break;

        case PX_BUILDER_CMD_INTEGER_32: {
            PxBuilderCmdInteger32 cmd = command.integer_32;

            result = pxMemory8WriteInteger32(memory, size,
                cmd.radix, cmd.options, cmd.value);
        } break;

        case PX_BUILDER_CMD_INTEGER_64: {
            PxBuilderCmdInteger64 cmd = command.integer_64;

            result = pxMemory8WriteInteger64(memory, size,
                cmd.radix, cmd.options, cmd.value);
        } break;

        case PX_BUILDER_CMD_INTEGER: {
            PxBuilderCmdInteger cmd = command.integer_word;

            result = pxMemory8WriteInteger(memory, size,
                cmd.radix, cmd.options, cmd.value);
        } break;

        case PX_BUILDER_CMD_BOOLEAN_8: {
            pxb8  cmd   = command.boolean_8;
            void* value = "false";

            result = 5;

            if (cmd != 0) {
                value  = "true";
                result = 4;
            }

            if (size >= result)
                pxMemoryCopy(memory, value, result, 1);
            else
                result = 0;
        } break;

        case PX_BUILDER_CMD_BOOLEAN_16: {
            pxb16 cmd   = command.boolean_16;
            void* value = "false";

            result = 5;

            if (cmd != 0) {
                value  = "true";
                result = 4;
            }

            if (size >= result)
                pxMemoryCopy(memory, value, result, 1);
            else
                result = 0;
        } break;

        case PX_BUILDER_CMD_BOOLEAN_32: {
            pxb32 cmd   = command.boolean_32;
            void* value = "false";

            result = 5;

            if (cmd != 0) {
                value  = "true";
                result = 4;
            }

            if (size >= result)
                pxMemoryCopy(memory, value, result, 1);
            else
                result = 0;
        } break;

        case PX_BUILDER_CMD_BOOLEAN_64: {
            pxb64 cmd   = command.boolean_64;
            void* value = "false";

            result = 5;

            if (cmd != 0) {
                value  = "true";
                result = 4;
            }

            if (size >= result)
                pxMemoryCopy(memory, value, result, 1);
            else
                result = 0;
        } break;

        case PX_BUILDER_CMD_BOOLEAN: {
            pxbword cmd   = command.boolean_word;
            void*   value = "false";

            result = 5;

            if (cmd != 0) {
                value  = "true";
                result = 4;
            }

            if (size >= result)
                pxMemoryCopy(memory, value, result, 1);
            else
                result = 0;
        } break;

        case PX_BUILDER_CMD_UNICODE: {
            result = pxUtf8WriteMemory8Forw(memory, size, 0, command.unicode);
        } break;

        case PX_BUILDER_CMD_STRING_8: {
            PxString8 cmd = command.string_8;

            if (cmd.length < 0 || cmd.length >= size)
                return 0;

            for (pxiword i = 0; i < cmd.length; i += 1)
                memory[i] = cmd.memory[i];

            result = cmd.length;
        } break;

        case PX_BUILDER_CMD_STRING_16: {
            PxString16 cmd = command.string_16;

            pxiword length = pxUtf32UnitsFromMemory16(
                cmd.memory, cmd.length);

            if (length < 0 || length >= size) return 0;

            pxiword index = 0;
            pxiword other = 0;

            while (index < length) {
                pxi32 unicode = 0;

                other += pxUtf16ReadMemory16Forw(
                    cmd.memory, cmd.length, other, &unicode);

                index += pxUtf8WriteMemory8Forw(
                    memory, length, index, unicode);
            }

            result = length;
        } break;

        case PX_BUILDER_CMD_STRING_32: {
            PxString32 cmd = command.string_32;

            pxiword length = pxUtf8UnitsFromMemory32(
                cmd.memory, cmd.length);

            if (length < 0 || length >= size) return 0;

            pxiword index = 0;
            pxiword other = 0;

            while (index < length) {
                pxi32 unicode = 0;

                other += pxUtf32ReadMemory32Forw(
                    cmd.memory, cmd.length, other, &unicode);

                index += pxUtf8WriteMemory8Forw(
                    memory, length, index, unicode);
            }

            result = length;
        } break;

        case PX_BUILDER_CMD_DELEGATE: {
            PxBuilderCmdDelegate cmd = command.delegate;

            result = pxCast(PxBuilderProc*, cmd.proc)
                (cmd.ctxt, self);
        }

        default: break;
    }

    self->size += result;

    return result;
}

PxString8
pxString8FromBuilder(PxArena* arena, PxBuilder* builder)
{
    PxString8 string = {
        .memory = builder->memory,
        .length = builder->size,
    };

    return pxString8Copy(arena, string);
}

PxString16
pxString16FromBuilder(PxArena* arena, PxBuilder* builder)
{
    PxString8 string = {
        .memory = builder->memory,
        .length = builder->size,
    };

    return pxString16CopyString8(arena, string);
}

PxString32
pxString32FromBuilder(PxArena* arena, PxBuilder* builder)
{
    PxString8 string = {
        .memory = builder->memory,
        .length = builder->size,
    };

    return pxString32CopyString8(arena, string);
}

#endif // PX_CORE_FORMAT_BUILDER_C
