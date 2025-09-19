#ifndef PX_JSON_TOKEN_C
#define PX_JSON_TOKEN_C

#include "token.h"

PxJsonToken
pxJsonTokenNone()
{
    return (PxJsonToken) {
        .type = PX_JSON_TOKEN_NONE,
    };
}

PxJsonToken
pxJsonTokenError(PxString8 subject, PxString8 content)
{
    return (PxJsonToken) {
        .type   = PX_JSON_TOKEN_ERROR,
        .length = subject.length,

        .error = {
            .subject = subject,
            .content = content,
        },
    };
}

PxJsonToken
pxJsonTokenObjectOpen()
{
    return (PxJsonToken) {
        .type   = PX_JSON_TOKEN_OBJECT_OPEN,
        .length = 1,
    };
}

PxJsonToken
pxJsonTokenObjectClose()
{
    return (PxJsonToken) {
        .type   = PX_JSON_TOKEN_OBJECT_CLOSE,
        .length = 1,
    };
}

PxJsonToken
pxJsonTokenArrayOpen()
{
    return (PxJsonToken) {
        .type   = PX_JSON_TOKEN_ARRAY_OPEN,
        .length = 1,
    };
}

PxJsonToken
pxJsonTokenArrayClose()
{
    return (PxJsonToken) {
        .type   = PX_JSON_TOKEN_ARRAY_CLOSE,
        .length = 1,
    };
}

PxJsonToken
pxJsonTokenColon()
{
    return (PxJsonToken) {
        .type   = PX_JSON_TOKEN_COLON,
        .length = 1,
    };
}

PxJsonToken
pxJsonTokenComma()
{
    return (PxJsonToken) {
        .type   = PX_JSON_TOKEN_COMMA,
        .length = 1,
    };
}

PxJsonToken
pxJsonTokenString(PxString8 string)
{
    return (PxJsonToken) {
        .type     = PX_JSON_TOKEN_STRING,
        .length   = string.length + 2,
        .string_8 = string,
    };
}

PxJsonToken
pxJsonTokenUnsigned(PxString8 string)
{
    PxFmtRadix radix = PX_FORMAT_RADIX_10;
    PxFmtFlag  flags = PX_FORMAT_FLAG_PLUS;

    pxuword value = 0;

    if (pxUnsignedFromString8(string, &value, radix, flags) == 0)
        return pxJsonTokenError(string, pxs8("Invalid number"));

    return (PxJsonToken) {
        .type          = PX_JSON_TOKEN_UNSIGNED,
        .length        = string.length,
        .unsigned_word = value,
    };
}

PxJsonToken
pxJsonTokenInteger(PxString8 string)
{
    PxFmtRadix radix = PX_FORMAT_RADIX_10;
    PxFmtFlag  flags = PX_FORMAT_FLAG_PLUS;

    pxiword value = 0;

    if (pxIntegerFromString8(string, &value, radix, flags) == 0)
        return pxJsonTokenError(string, pxs8("Invalid number"));

    return (PxJsonToken) {
        .type         = PX_JSON_TOKEN_INTEGER,
        .length       = string.length,
        .integer_word = value,
    };
}

PxJsonToken
pxJsonTokenFloating(PxString8 string)
{
    PxFmtRadix radix = PX_FORMAT_RADIX_10;
    PxFmtFlag  flags = PX_FORMAT_FLAG_PLUS;

    pxfword value = 0;

    if (1 /* pxFloatingFromString8(string, &value, radix, flags) == 0 */)
        return pxJsonTokenError(string, pxs8("Not implemented yet"));

    return (PxJsonToken) {
        .type          = PX_JSON_TOKEN_FLOATING,
        .length        = string.length,
        .floating_word = value,
    };
}

PxJsonToken
pxJsonTokenBoolean(PxString8 string, pxbword value)
{
    return (PxJsonToken) {
        .type         = PX_JSON_TOKEN_BOOLEAN,
        .length       = string.length,
        .boolean_word = value,
    };
}

PxJsonToken
pxJsonTokenNull(PxString8 string)
{
    return (PxJsonToken) {
        .type   = PX_JSON_TOKEN_NULL,
        .length = string.length,
    };
}

PxJsonToken
pxJsonTokenCount()
{
    return (PxJsonToken) {
        .type = PX_JSON_TOKEN_COUNT,
    };
}

pxb8
pxJsonIsLetter(pxu8 value)
{
    if (value >= PX_ASCII_LOWER_A && value <= PX_ASCII_LOWER_Z)
        return 1;

    if (value >= PX_ASCII_UPPER_A && value <= PX_ASCII_UPPER_Z)
        return 1;

    return 0;
}

pxb8
pxJsonIsNumber(pxu8 value)
{
    if (value >= PX_ASCII_ZERO && value <= PX_ASCII_NINE)
        return 1;

    return 0;
}

pxb8
pxJsonIsNumeric(pxu8 value)
{
    if (value >= PX_ASCII_ZERO && value <= PX_ASCII_NINE)
        return 1;

    if (value == PX_ASCII_PLUS)  return 1;
    if (value == PX_ASCII_MINUS) return 1;
    if (value == PX_ASCII_POINT) return 1;

    if (value == PX_ASCII_LOWER_E) return 1;
    if (value == PX_ASCII_UPPER_E) return 1;

    return 0;
}

PxJsonToken
pxJsonPeek(PxReader* reader, PxArena* arena)
{
    pxu8 byte = pxJsonSkipSpaces(reader);

    switch (byte) {
        case PX_ASCII_NULL:
            return pxJsonTokenCount();

        case PX_ASCII_BRACE_LEFT:
        case PX_ASCII_BRACE_RIGHT:
        case PX_ASCII_SQUARE_LEFT:
        case PX_ASCII_SQUARE_RIGHT:
        case PX_ASCII_COLON:
        case PX_ASCII_COMMA:
            return pxJsonPeekSymbol(reader, arena);

        case PX_ASCII_PLUS:
        case PX_ASCII_MINUS:
        case PX_ASCII_ZERO:
        case PX_ASCII_ONE:
        case PX_ASCII_TWO:
        case PX_ASCII_THREE:
        case PX_ASCII_FOUR:
        case PX_ASCII_FIVE:
        case PX_ASCII_SIX:
        case PX_ASCII_SEVEN:
        case PX_ASCII_EIGHT:
        case PX_ASCII_NINE:
            return pxJsonPeekNumber(reader, arena);

        case PX_ASCII_LOWER_T:
        case PX_ASCII_LOWER_F:
        case PX_ASCII_LOWER_N:
            return pxJsonPeekWord(reader, arena);

        default: break;
    }

    PxString8 message =
        pxString8Copy(arena, pxs8("Unknown symbol"));

    PxString8 subject = pxString8CopyUnicode(arena, byte);

    return pxJsonTokenError(subject, message);
}

PxJsonToken
pxJsonPeekSymbol(PxReader* reader, PxArena* arena)
{
    pxu8 byte = pxReaderPeekByte(reader, 0);

    switch (byte) {
        case PX_ASCII_BRACE_LEFT:
            return pxJsonTokenObjectOpen();

        case PX_ASCII_BRACE_RIGHT:
            return pxJsonTokenObjectClose();

        case PX_ASCII_SQUARE_LEFT:
            return pxJsonTokenArrayOpen();

        case PX_ASCII_SQUARE_RIGHT:
            return pxJsonTokenArrayClose();

        case PX_ASCII_COLON:
            return pxJsonTokenColon();

        case PX_ASCII_COMMA:
            return pxJsonTokenComma();

        default: break;
    }

    PxString8 message =
        pxString8Copy(arena, pxs8("Unknown symbol"));

    PxString8 subject = pxString8CopyUnicode(arena, byte);

    return pxJsonTokenError(subject, message);
}

PxJsonToken
pxJsonPeekString(PxReader* reader, PxArena* arena)
{
    pxu8    byte = pxReaderPeekByte(reader, 0);
    pxiword size = 0;

    if (byte != PX_ASCII_QUOTE) {
        PxString8 message = pxString8Copy(arena,
            pxs8("Invalid string, expected opening {\"}"));

        PxString8 subject = pxString8CopyUnicode(arena, byte);

        return pxJsonTokenError(subject, message);
    }

    size += 1;
    byte  = pxReaderPeekByte(reader, size);

    while (byte != PX_ASCII_NULL && byte != PX_ASCII_QUOTE) {
        size += 1;
        byte  = pxReaderPeekByte(reader, size);
    }

    if (byte != PX_ASCII_QUOTE) {
        PxString8 message = pxString8Copy(arena,
            pxs8("Invalid string, expected closing {\"}"));

        PxString8 subject = pxString8CopyUnicode(arena, byte);

        return pxJsonTokenError(subject, message);
    }

    PxString8 string =
        pxReaderPeekString8(reader, arena, size - 1, 1, 0);

    return pxJsonTokenString(string);
}

PxJsonToken
pxJsonPeekNumber(PxReader* reader, PxArena* arena)
{
    pxu8    byte = pxReaderPeekByte(reader, 0);
    pxiword size = 0;

    PxJsonTokenType type = PX_JSON_TOKEN_NONE;

    while (pxJsonIsNumeric(byte) != 0) {
        switch (byte) {
            case PX_ASCII_PLUS:
            case PX_ASCII_ZERO:
            case PX_ASCII_ONE:
            case PX_ASCII_TWO:
            case PX_ASCII_THREE:
            case PX_ASCII_FOUR:
            case PX_ASCII_FIVE:
            case PX_ASCII_SIX:
            case PX_ASCII_SEVEN:
            case PX_ASCII_EIGHT:
            case PX_ASCII_NINE:
                if (type == PX_JSON_TOKEN_NONE)
                    type = PX_JSON_TOKEN_UNSIGNED;
            break;

            case PX_ASCII_MINUS:
                if (type == PX_JSON_TOKEN_NONE)
                    type = PX_JSON_TOKEN_INTEGER;
            break;

            case PX_ASCII_POINT:
            case PX_ASCII_LOWER_E:
            case PX_ASCII_UPPER_E:
                type = PX_JSON_TOKEN_FLOATING;
            break;

            default: {
                PxString8 message = pxString8Copy(arena,
                    pxs8("Invalid number, expected digit or [+-.eE]"));

                PxString8 subject = pxString8CopyUnicode(arena, byte);

                return pxJsonTokenError(subject, message);
            } break;
        }

        size += 1;
        byte  = pxReaderPeekByte(reader, size);
    }

    PxString8 string = pxReaderPeekString8(reader, arena, size, 0, 0);

    switch (type) {
        case PX_JSON_TOKEN_UNSIGNED:
            return pxJsonTokenUnsigned(string);

        case PX_JSON_TOKEN_INTEGER:
            return pxJsonTokenInteger(string);

        case PX_JSON_TOKEN_FLOATING:
            return pxJsonTokenFloating(string);

        default: break;
    }

    PxString8 message = pxString8Copy(arena,
        pxs8("Invalid number, syntactic or overflow"));

    return pxJsonTokenError(string, message);
}

PxJsonToken
pxJsonPeekWord(PxReader* reader, PxArena* arena)
{
    pxu8    byte = pxReaderPeekByte(reader, 0);
    pxiword size = 0;

    if (pxJsonIsLetter(byte) == 0) {
        PxString8 subject = pxString8Copy(arena,
            pxs8("Invalid key word, expected opening letter"));

        PxString8 message = pxString8CopyUnicode(arena, byte);

        return pxJsonTokenError(subject, message);
    }

    size += 1;
    byte  = pxReaderPeekByte(reader, size);

    while (pxJsonIsLetter(byte) != 0 || pxJsonIsNumber(byte) != 0) {
        size += 1;
        byte  = pxReaderPeekByte(reader, size);
    }

    PxString8 string = pxReaderPeekString8(reader, arena, size, 0, 0);

    if (pxString8IsEqual(string, pxs8("true")) != 0)
        return pxJsonTokenBoolean(string, 1);

    if (pxString8IsEqual(string, pxs8("false")) != 0)
        return pxJsonTokenBoolean(string, 0);

    if (pxString8IsEqual(string, pxs8("null")) != 0)
        return pxJsonTokenNull(string);

    PxString8 message =
        pxString8Copy(arena, pxs8("Invalid key word"));

    return pxJsonTokenError(string, message);
}

PxJsonToken
pxJsonNext(PxReader* reader, PxArena* arena)
{
    pxu8 byte = pxJsonSkipSpaces(reader);

    PxJsonToken result = pxJsonTokenNone();

    switch (byte) {
        case PX_ASCII_NULL:
            result = pxJsonTokenCount();
        break;

        case PX_ASCII_BRACE_LEFT:
        case PX_ASCII_BRACE_RIGHT:
        case PX_ASCII_SQUARE_LEFT:
        case PX_ASCII_SQUARE_RIGHT:
        case PX_ASCII_COLON:
        case PX_ASCII_COMMA:
            result = pxJsonPeekSymbol(reader, arena);
        break;

        case PX_ASCII_QUOTE:
            result = pxJsonPeekString(reader, arena);
        break;

        case PX_ASCII_PLUS:
        case PX_ASCII_MINUS:
        case PX_ASCII_ZERO:
        case PX_ASCII_ONE:
        case PX_ASCII_TWO:
        case PX_ASCII_THREE:
        case PX_ASCII_FOUR:
        case PX_ASCII_FIVE:
        case PX_ASCII_SIX:
        case PX_ASCII_SEVEN:
        case PX_ASCII_EIGHT:
        case PX_ASCII_NINE:
            result = pxJsonPeekNumber(reader, arena);
        break;

        case PX_ASCII_LOWER_T:
        case PX_ASCII_LOWER_F:
        case PX_ASCII_LOWER_N:
            result = pxJsonPeekWord(reader, arena);
        break;

        default: break;
    }

    if (result.type == PX_JSON_TOKEN_NONE) {
        PxString8 message =
            pxString8Copy(arena, pxs8("Unknown symbol"));

        PxString8 subject = pxString8CopyUnicode(arena, byte);

        return pxJsonTokenError(subject, message);
    }

    pxReaderSkip(reader, result.length);

    return result;
}

pxu8
pxJsonSkipSpaces(PxReader* reader)
{
    pxu8 byte = pxReaderPeekByte(reader, 0);

    while (pxUnicodeIsAsciiCntrl(byte) != 0 && byte != 0)
        byte = pxReaderNextByte(reader, 1);

    return byte;
}

#endif // PX_JSON_TOKEN_C
