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

    return pxString8Make(memory, index + 1);
}

PxFormatCmd
pxFormatCmdUnsigned8(pxuword radix, PxFormatFlag flags, pxu8 value)
{
    return (PxFormatCmd) {
        .type = PX_FORMAT_CMD_UNSIGNED_8,

        .unsigned_8 = {
            .radix   = radix,
            .flags = flags,
            .value   = value,
        },
    };
}

PxFormatCmd
pxFormatCmdUnsigned16(pxuword radix, PxFormatFlag flags, pxu16 value)
{
    return (PxFormatCmd) {
        .type = PX_FORMAT_CMD_UNSIGNED_16,

        .unsigned_16 = {
            .radix   = radix,
            .flags = flags,
            .value   = value,
        },
    };
}

PxFormatCmd
pxFormatCmdUnsigned32(pxuword radix, PxFormatFlag flags, pxu32 value)
{
    return (PxFormatCmd) {
        .type = PX_FORMAT_CMD_UNSIGNED_32,

        .unsigned_32 = {
            .radix   = radix,
            .flags = flags,
            .value   = value,
        },
    };
}

PxFormatCmd
pxFormatCmdUnsigned64(pxuword radix, PxFormatFlag flags, pxu64 value)
{
    return (PxFormatCmd) {
        .type = PX_FORMAT_CMD_UNSIGNED_64,

        .unsigned_64 = {
            .radix   = radix,
            .flags = flags,
            .value   = value,
        },
    };
}

PxFormatCmd
pxFormatCmdUnsigned(pxuword radix, PxFormatFlag flags, pxuword value)
{
    return (PxFormatCmd) {
        .type = PX_FORMAT_CMD_UNSIGNED,

        .unsigned_word = {
            .radix   = radix,
            .flags = flags,
            .value   = value,
        },
    };
}

PxFormatCmd
pxFormatCmdInteger8(pxuword radix, PxFormatFlag flags, pxi8 value)
{
    return (PxFormatCmd) {
        .type = PX_FORMAT_CMD_INTEGER_8,

        .integer_8 = {
            .radix   = radix,
            .flags = flags,
            .value   = value,
        },
    };
}

PxFormatCmd
pxFormatCmdInteger16(pxuword radix, PxFormatFlag flags, pxi16 value)
{
    return (PxFormatCmd) {
        .type = PX_FORMAT_CMD_INTEGER_16,

        .integer_16 = {
            .radix   = radix,
            .flags = flags,
            .value   = value,
        },
    };
}

PxFormatCmd
pxFormatCmdInteger32(pxuword radix, PxFormatFlag flags, pxi32 value)
{
    return (PxFormatCmd) {
        .type = PX_FORMAT_CMD_INTEGER_32,

        .integer_32 = {
            .radix   = radix,
            .flags = flags,
            .value   = value,
        },
    };
}

PxFormatCmd
pxFormatCmdInteger64(pxuword radix, PxFormatFlag flags, pxi64 value)
{
    return (PxFormatCmd) {
        .type = PX_FORMAT_CMD_INTEGER_64,

        .integer_64 = {
            .radix   = radix,
            .flags = flags,
            .value   = value,
        },
    };
}

PxFormatCmd
pxFormatCmdInteger(pxuword radix, PxFormatFlag flags, pxiword value)
{
    return (PxFormatCmd) {
        .type = PX_FORMAT_CMD_INTEGER,

        .integer_word = {
            .radix   = radix,
            .flags = flags,
            .value   = value,
        },
    };
}

PxFormatCmd
pxFormatCmdBoolean8(pxb8 value)
{
    return (PxFormatCmd) {
        .type      = PX_FORMAT_CMD_BOOLEAN_8,
        .boolean_8 = value,
    };
}

PxFormatCmd
pxFormatCmdBoolean16(pxb16 value)
{
    return (PxFormatCmd) {
        .type      = PX_FORMAT_CMD_BOOLEAN_16,
        .boolean_16 = value,
    };
}

PxFormatCmd
pxFormatCmdBoolean32(pxb32 value)
{
    return (PxFormatCmd) {
        .type       = PX_FORMAT_CMD_BOOLEAN_32,
        .boolean_32 = value,
    };
}

PxFormatCmd
pxFormatCmdBoolean64(pxb64 value)
{
    return (PxFormatCmd) {
        .type       = PX_FORMAT_CMD_BOOLEAN_64,
        .boolean_64 = value,
    };
}

PxFormatCmd
pxFormatCmdBoolean(pxbword value)
{
    return (PxFormatCmd) {
        .type         = PX_FORMAT_CMD_BOOLEAN,
        .boolean_word = value,
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
pxBuilderFormat(PxBuilder* self, PxString8 format, pxiword start, pxiword stop, PxFormatCmd* list)
{
    pxiword index = 0;
    pxiword size  = self->size;
    pxb8    state = 0;

    PxFormatCmd command = {0};

    PxString8 left  = {0};
    PxString8 right = format;

    while (pxString8Contains(right, pxs8("$")) > 0) {
        pxString8Split(right, pxs8("$"), &left, &right);

        command = pxFormatCmdString8(left);

        if (pxBuilderCommand(self, command) == 0) break;

        left  = pxFormatSpecFromString8(right);
        right = pxString8SliceHead(right, left.length);

        state = pxIntegerFromString8(&index, 10, 0,
            pxString8Slice(left, 1, left.length - 1));

        if (index < start || index >= stop || state == 0)
            command = pxFormatCmdString8(pxs8("${?}"));
        else
            command = list[index];

        if (pxBuilderCommand(self, command) == 0) break;
    }

    command = pxFormatCmdString8(right);

    pxBuilderCommand(self, command);

    return self->size - size;
}

pxiword
pxBuilderChain(PxBuilder* self, pxiword start, pxiword stop, PxFormatCmd* list)
{
    if (list == 0 || stop <= start) return 0;

    pxiword size = self->size;

    for (pxiword i = start; i < stop; i += 1) {
        if (pxBuilderCommand(self, list[i]) == 0)
            break;
    }

    return self->size - size;
}

pxiword
pxBuilderCommand(PxBuilder* self, PxFormatCmd command)
{
    pxu8*   memory = self->memory + self->size;
    pxiword size   = self->length - self->size;
    pxiword result = 0;

    switch (command.type) {
        case PX_FORMAT_CMD_UNSIGNED_8: {
            PxFormatCmdUnsigned8 cmd = command.unsigned_8;

            result = pxMemory8WriteUnsigned8(memory, size,
                cmd.radix, cmd.flags, cmd.value);
        } break;

        case PX_FORMAT_CMD_UNSIGNED_16: {
            PxFormatCmdUnsigned16 cmd = command.unsigned_16;

            result = pxMemory8WriteUnsigned16(memory, size,
                cmd.radix, cmd.flags, cmd.value);
        } break;

        case PX_FORMAT_CMD_UNSIGNED_32: {
            PxFormatCmdUnsigned32 cmd = command.unsigned_32;

            result = pxMemory8WriteUnsigned32(memory, size,
                cmd.radix, cmd.flags, cmd.value);
        } break;

        case PX_FORMAT_CMD_UNSIGNED_64: {
            PxFormatCmdUnsigned64 cmd = command.unsigned_64;

            result = pxMemory8WriteUnsigned64(memory, size,
                cmd.radix, cmd.flags, cmd.value);
        } break;

        case PX_FORMAT_CMD_UNSIGNED: {
            PxFormatCmdUnsigned cmd = command.unsigned_word;

            result = pxMemory8WriteUnsigned(memory, size,
                cmd.radix, cmd.flags, cmd.value);
        } break;

        case PX_FORMAT_CMD_INTEGER_8: {
            PxFormatCmdInteger8 cmd = command.integer_8;

            result = pxMemory8WriteInteger8(memory, size,
                cmd.radix, cmd.flags, cmd.value);
        } break;

        case PX_FORMAT_CMD_INTEGER_16: {
            PxFormatCmdInteger16 cmd = command.integer_16;

            result = pxMemory8WriteInteger16(memory, size,
                cmd.radix, cmd.flags, cmd.value);
        } break;

        case PX_FORMAT_CMD_INTEGER_32: {
            PxFormatCmdInteger32 cmd = command.integer_32;

            result = pxMemory8WriteInteger32(memory, size,
                cmd.radix, cmd.flags, cmd.value);
        } break;

        case PX_FORMAT_CMD_INTEGER_64: {
            PxFormatCmdInteger64 cmd = command.integer_64;

            result = pxMemory8WriteInteger64(memory, size,
                cmd.radix, cmd.flags, cmd.value);
        } break;

        case PX_FORMAT_CMD_INTEGER: {
            PxFormatCmdInteger cmd = command.integer_word;

            result = pxMemory8WriteInteger(memory, size,
                cmd.radix, cmd.flags, cmd.value);
        } break;

        case PX_FORMAT_CMD_BOOLEAN_8: {
            pxbword   cmd   = command.boolean_8;
            PxString8 value = pxs8("false");

            if (cmd != 0) value = pxs8("true");

            result = value.length;

            if (size >= result)
                pxMemoryCopy(memory, value.memory, value.length, 1);
            else
                result = 0;
        } break;

        case PX_FORMAT_CMD_BOOLEAN_16: {
            pxbword   cmd   = command.boolean_16;
            PxString8 value = pxs8("false");

            if (cmd != 0) value = pxs8("true");

            result = value.length;

            if (size >= result)
                pxMemoryCopy(memory, value.memory, value.length, 1);
            else
                result = 0;
        } break;

        case PX_FORMAT_CMD_BOOLEAN_32: {
            pxbword   cmd   = command.boolean_32;
            PxString8 value = pxs8("false");

            if (cmd != 0) value = pxs8("true");

            result = value.length;

            if (size >= result)
                pxMemoryCopy(memory, value.memory, value.length, 1);
            else
                result = 0;
        } break;

        case PX_FORMAT_CMD_BOOLEAN_64: {
            pxbword   cmd   = command.boolean_64;
            PxString8 value = pxs8("false");

            if (cmd != 0) value = pxs8("true");

            result = value.length;

            if (size >= result)
                pxMemoryCopy(memory, value.memory, value.length, 1);
            else
                result = 0;
        } break;

        case PX_FORMAT_CMD_BOOLEAN: {
            pxbword   cmd   = command.boolean_word;
            PxString8 value = pxs8("false");

            if (cmd != 0) value = pxs8("true");

            result = value.length;

            if (size >= result)
                pxMemoryCopy(memory, value.memory, value.length, 1);
            else
                result = 0;
        } break;

        case PX_FORMAT_CMD_UNICODE: {
            result = pxUtf8WriteMemory8Forw(memory, size,
                0, command.unicode);
        } break;

        case PX_FORMAT_CMD_STRING_8: {
            result = pxMemory8WriteString8(memory, size,
                command.string_8);
        } break;

        case PX_FORMAT_CMD_STRING_16: {
            result = pxMemory8WriteString16(memory, size,
                command.string_16);
        } break;

        case PX_FORMAT_CMD_STRING_32: {
            result = pxMemory8WriteString32(memory, size,
                command.string_32);
        } break;

        case PX_FORMAT_CMD_DELEGATE: {
            PxFormatCmdDelegate cmd = command.delegate;

            result = pxCast(PxFormatProc*, cmd.proc)
                (cmd.ctxt, self);
        } break;

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
