#ifndef PX_CORE_FORMAT_PRINTING_C
#define PX_CORE_FORMAT_PRINTING_C

#include "printing.h"

static PxString8
pxString8MatchFmtSpec(PxString8 string)
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

PxPrintCmd
pxPrintCmdString8(PxString8 value)
{
    return (PxPrintCmd) {
        .type  = PX_PRINT_CMD_STRING_8,
        .radix = PX_FORMAT_RADIX_10,
        .flags = PX_FORMAT_FLAG_NONE,

        .string_8 = value,
    };
}

PxPrintCmd
pxPrintCmdString16(PxString16 value)
{
    return (PxPrintCmd) {
        .type  = PX_PRINT_CMD_STRING_16,
        .radix = PX_FORMAT_RADIX_10,
        .flags = PX_FORMAT_FLAG_NONE,

        .string_16 = value,
    };
}

PxPrintCmd
pxPrintCmdString32(PxString32 value)
{
    return (PxPrintCmd) {
        .type  = PX_PRINT_CMD_STRING_32,
        .radix = PX_FORMAT_RADIX_10,
        .flags = PX_FORMAT_FLAG_NONE,

        .string_32 = value,
    };
}

PxPrintCmd
pxPrintCmdUnicode(pxi32 value)
{
    return (PxPrintCmd) {
        .type  = PX_PRINT_CMD_UNICODE,
        .radix = PX_FORMAT_RADIX_10,
        .flags = PX_FORMAT_FLAG_NONE,

        .unicode = value,
    };
}

PxPrintCmd
pxPrintCmdUnsigned(pxuword value)
{
    return (PxPrintCmd) {
        .type  = PX_PRINT_CMD_UNSIGNED,
        .radix = PX_FORMAT_RADIX_10,
        .flags = PX_FORMAT_FLAG_NONE,

        .unsigned_word = value,
    };
}

PxPrintCmd
pxPrintCmdInteger(pxiword value)
{
    return (PxPrintCmd) {
        .type  = PX_PRINT_CMD_INTEGER,
        .radix = PX_FORMAT_RADIX_10,
        .flags = PX_FORMAT_FLAG_NONE,

        .integer_word = value,
    };
}

PxPrintCmd
pxPrintCmdFloating(pxfword value)
{
    return (PxPrintCmd) {
        .type  = PX_PRINT_CMD_FLOATING,
        .radix = PX_FORMAT_RADIX_10,
        .flags = PX_FORMAT_FLAG_NONE,

        .floating_word = value,
    };
}

PxPrintCmd
pxPrintCmdBoolean(pxbword value)
{
    return (PxPrintCmd) {
        .type  = PX_PRINT_CMD_BOOLEAN,
        .radix = PX_FORMAT_RADIX_10,
        .flags = PX_FORMAT_FLAG_NONE,

        .boolean_word = value,
    };
}

pxb8
pxBuffer8PrintCmdHead(PxBuffer8* self, PxPrintCmd value)
{
    switch (value.type) {
        case PX_PRINT_CMD_STRING_8: {
            if (value.string_8.length <= 0) return 1;

            if (pxBuffer8WriteString8Head(self, value.string_8) != 0)
                return 1;
        } break;

        case PX_PRINT_CMD_STRING_16: {
            if (value.string_16.length <= 0) return 1;

            if (pxBuffer8WriteString16Head(self, value.string_16) != 0)
                return 1;
        } break;

        case PX_PRINT_CMD_STRING_32: {
            if (value.string_32.length <= 0) return 1;

            if (pxBuffer8WriteString32Head(self, value.string_32) != 0)
                return 1;
        } break;

        case PX_PRINT_CMD_UNICODE: {
            if (pxBuffer8WriteUnicodeHead(self, value.unicode) != 0)
                return 1;
        } break;

        case PX_PRINT_CMD_UNSIGNED: {
            pxiword size = pxBuffer8WriteUnsignedHead(self,
                value.unsigned_word, value.radix, value.flags);

            if (size > 0) return 1;
        } break;

        case PX_PRINT_CMD_INTEGER: {
            pxiword size = pxBuffer8WriteIntegerHead(self,
                value.integer_word, value.radix, value.flags);

            if (size > 0) return 1;
        } break;

        case PX_PRINT_CMD_FLOATING: {
            pxiword size = 1; /* pxBuffer8WriteFloatingHead(self,
                value.floating_word, value.radix, value.flags); */

            if (size > 0) return 1;
        } break;

        case PX_PRINT_CMD_BOOLEAN: {
            pxiword size = pxBuffer8WriteBooleanHead(self,
                value.boolean_word, value.flags);

            if (size > 0) return 1;
        } break;

        default: break;
    }

    return 0;
}

pxb8
pxBuffer8PrintCmdTail(PxBuffer8* self, PxPrintCmd value)
{
    switch (value.type) {
        case PX_PRINT_CMD_STRING_8: {
            if (value.string_8.length <= 0) return 1;

            if (pxBuffer8WriteString8Tail(self, value.string_8) != 0)
                return 1;
        } break;

        case PX_PRINT_CMD_STRING_16: {
            if (value.string_16.length <= 0) return 1;

            if (pxBuffer8WriteString16Tail(self, value.string_16) != 0)
                return 1;
        } break;

        case PX_PRINT_CMD_STRING_32: {
            if (value.string_32.length <= 0) return 1;

            if (pxBuffer8WriteString32Tail(self, value.string_32) != 0)
                return 1;
        } break;

        case PX_PRINT_CMD_UNICODE: {
            if (pxBuffer8WriteUnicodeTail(self, value.unicode) != 0)
                return 1;
        } break;

        case PX_PRINT_CMD_UNSIGNED: {
            pxiword size = pxBuffer8WriteUnsignedTail(self,
                value.unsigned_word, value.radix, value.flags);

            if (size > 0) return 1;
        } break;

        case PX_PRINT_CMD_INTEGER: {
            pxiword size = pxBuffer8WriteIntegerTail(self,
                value.integer_word, value.radix, value.flags);

            if (size > 0) return 1;
        } break;

        case PX_PRINT_CMD_FLOATING: {
            pxiword size = 1; /* pxBuffer8WriteFloatingTail(self,
                value.floating_word, value.radix, value.flags); */

            if (size > 0) return 1;
        } break;

        case PX_PRINT_CMD_BOOLEAN: {
            pxiword size = pxBuffer8WriteBooleanTail(self,
                value.boolean_word, value.flags);

            if (size > 0) return 1;
        } break;

        default: break;
    }

    return 0;
}

pxb8
pxBuffer8PrintListHead(PxBuffer8* self, PxPrintCmd* values, pxiword length)
{
    pxiword size  = self->size;
    pxb8    state = 0;

    for (pxiword i = length; i > 0; i -= 1) {
        state =
            pxBuffer8PrintCmdHead(self, values[i - 1]);

        if (state == 0) break;
    }

    if (state == 0)
        pxBuffer8DropHead(self, self->size - size);

    return state;
}

pxb8
pxBuffer8PrintListTail(PxBuffer8* self, PxPrintCmd* values, pxiword length)
{
    pxiword size  = self->size;
    pxb8    state = 0;

    for (pxiword i = 0; i < length; i += 1) {
        state =
            pxBuffer8PrintCmdTail(self, values[i]);

        if (state == 0) break;
    }

    if (state == 0)
        pxBuffer8DropTail(self, self->size - size);

    return state;
}

pxb8
pxBuffer8PrintFmtTail(PxBuffer8* self, PxString8 format, PxPrintCmd* values, pxiword length)
{
    PxString8 left  = {0};
    PxString8 right = format;

    pxiword size  = self->size;
    pxiword index = 0;
    pxb8    state = 0;

    while (right.length > 0) {
        pxString8Split(right, pxs8("$"), &left, &right);

        state = pxBuffer8PrintCmdTail(self, pxPrintCmdString8(left));

        if (state == 0 || right.length <= 0) break;

        left  = pxString8MatchFmtSpec(right);
        right = pxString8SliceHead(right, left.length + 2);

        state = pxIntegerFromString8(left, &index, 10, 0);

        if (state == 0 || index < 0 || index >= length)
            continue;

        state = pxBuffer8PrintCmdTail(self, values[index]);

        if (state == 0) break;
    }

    if (state == 0)
        pxBuffer8DropTail(self, self->size - size);

    return state;
}

pxiword
pxWriterNextPrintCmd(PxWriter* self, PxPrintCmd value)
{
    switch (value.type) {
        case PX_PRINT_CMD_STRING_8: {
            return pxWriterNextString8(self, value.string_8);
        } break;

        case PX_PRINT_CMD_STRING_16: {
            return pxWriterNextString16(self, value.string_16);
        } break;

        case PX_PRINT_CMD_STRING_32: {
            return pxWriterNextString32(self, value.string_32);
        } break;

        case PX_PRINT_CMD_UNICODE: {
            return pxWriterNextUnicode(self, value.unicode);
        } break;

        case PX_PRINT_CMD_UNSIGNED: {
            return pxWriterNextUnsigned(self,
                value.unsigned_word, value.radix, value.flags);
        } break;

        case PX_PRINT_CMD_INTEGER: {
            return pxWriterNextInteger(self,
                value.integer_word, value.radix, value.flags);
        } break;

        case PX_PRINT_CMD_FLOATING: {
            return 0; /* pxWriterNextFloating(self,
                value.floating_word, value.radix, value.flags); */
        } break;

        case PX_PRINT_CMD_BOOLEAN: {
            return pxWriterNextBoolean(self,
                value.boolean_word, value.flags);
        } break;

        default: break;
    }

    return 0;
}

pxiword
pxWriterNextPrintList(PxWriter* self, PxPrintCmd* values, pxiword length)
{
    pxiword result = 0;

    for (pxiword i = 0; i < length; i += 1)
        result += pxWriterNextPrintCmd(self, values[i]);

    return result;
}

pxiword
pxWriterNextFmt(PxWriter* self, PxString8 format, PxPrintCmd* values, pxiword length)
{
    PxString8 left  = {0};
    PxString8 right = format;

    pxiword result = 0;
    pxiword index  = 0;
    pxb8    state  = 0;

    while (right.length > 0) {
        pxString8Split(right, pxs8("$"), &left, &right);

        result += pxWriterNextPrintCmd(self, pxPrintCmdString8(left));

        if (right.length <= 0) break;

        left  = pxString8MatchFmtSpec(right);
        right = pxString8SliceHead(right, left.length + 2);

        state = pxIntegerFromString8(left, &index, 10, 0);

        if (state == 0 || index < 0 || index >= length)
            continue;

        result += pxWriterNextPrintCmd(self, values[index]);
    }

    return result;
}

#endif // PX_CORE_FORMAT_PRINTING_C
