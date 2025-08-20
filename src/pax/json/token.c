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
pxJsonTokenError(PxString8 string, PxString8 error)
{
    return (PxJsonToken) {
        .type   = PX_JSON_TOKEN_ERROR,
        .length = string.length,
        .string = string,
        .error  = error,
    };
}

PxJsonToken
pxJsonTokenObjectOpen(PxString8 string)
{
    return (PxJsonToken) {
        .type   = PX_JSON_TOKEN_OBJECT_OPEN,
        .length = string.length,
        .string = string,
    };
}

PxJsonToken
pxJsonTokenObjectClose(PxString8 string)
{
    return (PxJsonToken) {
        .type   = PX_JSON_TOKEN_OBJECT_CLOSE,
        .length = string.length,
        .string = string,
    };
}

PxJsonToken
pxJsonTokenArrayOpen(PxString8 string)
{
    return (PxJsonToken) {
        .type   = PX_JSON_TOKEN_ARRAY_OPEN,
        .length = string.length,
        .string = string,
    };
}

PxJsonToken
pxJsonTokenArrayClose(PxString8 string)
{
    return (PxJsonToken) {
        .type   = PX_JSON_TOKEN_ARRAY_CLOSE,
        .length = string.length,
        .string = string,
    };
}

PxJsonToken
pxJsonTokenColon(PxString8 string)
{
    return (PxJsonToken) {
        .type   = PX_JSON_TOKEN_COLON,
        .length = string.length,
        .string = string,
    };
}

PxJsonToken
pxJsonTokenComma(PxString8 string)
{
    return (PxJsonToken) {
        .type   = PX_JSON_TOKEN_COMMA,
        .length = string.length,
        .string = string,
    };
}

PxJsonToken
pxJsonTokenString(PxString8 string)
{
    return (PxJsonToken) {
        .type   = PX_JSON_TOKEN_STRING,
        .length = string.length + 2,
        .string = string,
    };
}

PxJsonToken
pxJsonTokenUnsigned(PxString8 string, pxunsig value)
{
    return (PxJsonToken) {
        .type   = PX_JSON_TOKEN_UNSIGNED,
        .length = string.length,
        .string = string,
        .uvalue = value,
    };
}

PxJsonToken
pxJsonTokenInteger(PxString8 string, pxint value)
{
    return (PxJsonToken) {
        .type   = PX_JSON_TOKEN_INTEGER,
        .length = string.length,
        .string = string,
        .ivalue = value,
    };
}

PxJsonToken
pxJsonTokenFloating(PxString8 string, pxfloat value)
{
    return (PxJsonToken) {
        .type   = PX_JSON_TOKEN_FLOATING,
        .length = string.length,
        .string = string,
        .fvalue = value,
    };
}

PxJsonToken
pxJsonTokenBoolean(PxString8 string, pxbool value)
{
    return (PxJsonToken) {
        .type   = PX_JSON_TOKEN_COMMA,
        .length = string.length,
        .string = string,
        .bvalue = value,
    };
}

PxJsonToken
pxJsonTokenNull(PxString8 string)
{
    return (PxJsonToken) {
        .type   = PX_JSON_TOKEN_NULL,
        .length = string.length,
        .string = string,
    };
}

PxJsonToken
pxJsonTokenCount()
{
    return (PxJsonToken) {
        .type = PX_JSON_TOKEN_COUNT,
    };
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

    PxString8 error  = pxString8Copy(arena, pxStr8("Unkown symbol"));
    PxString8 string = pxString8FromUnicode(arena, byte);

    return pxJsonTokenError(string, error);
}

PxJsonToken
pxJsonPeekSymbol(PxReader* reader, PxArena* arena)
{
    pxint offset = 1;
    pxu8  byte   = pxReaderPeek(reader, 0);

    PxString8 string = pxString8FromUnicode(arena, byte);

    switch (byte) {
        case PX_ASCII_BRACE_LEFT:
            return pxJsonTokenObjectOpen(string);

        case PX_ASCII_BRACE_RIGHT:
            return pxJsonTokenObjectClose(string);

        case PX_ASCII_SQUARE_LEFT:
            return pxJsonTokenArrayOpen(string);

        case PX_ASCII_SQUARE_RIGHT:
            return pxJsonTokenArrayClose(string);

        case PX_ASCII_COLON:
            return pxJsonTokenColon(string);

        case PX_ASCII_COMMA:
            return pxJsonTokenComma(string);

        default: break;
    }

    PxString8 error = pxString8Copy(arena, pxStr8("Unkown symbol"));

    return pxJsonTokenError(string, error);
}

PxJsonToken
pxJsonPeekString(PxReader* reader, PxArena* arena)
{
    pxint offset = 0;
    pxu8  byte   = pxReaderPeek(reader, offset);

    if (byte != PX_ASCII_QUOTE) {
        PxString8 error = pxString8Copy(arena,
            pxStr8("Invalid string, expected opening {\"}"));

        PxString8 string = pxString8FromUnicode(arena, byte);

        return pxJsonTokenError(string, error);
    }

    do {
        offset += 1;
        byte    = pxReaderPeek(reader, offset);
    } while (byte != PX_ASCII_QUOTE);

    if (byte != PX_ASCII_QUOTE) {
        PxString8 error = pxString8Copy(arena,
            pxStr8("Invalid string, expected closing {\"}"));

        PxString8 string = pxString8FromUnicode(arena, byte);

        return pxJsonTokenError(string, error);
    }

    PxString8 string = pxReaderPeekString(reader, arena, offset);

    return pxJsonTokenString(
        pxString8SliceLength(string, 1, string.length - 1));
}

PxJsonToken
pxJsonPeekNumber(PxReader* reader, PxArena* arena)
{
    pxint offset = 0;
    pxu8  byte   = pxReaderPeek(reader, offset);

    PxJsonToken result = pxJsonTokenNone();

    while (pxAsciiIsNumeric(byte, 10) != 0) {
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
                if (result.type == PX_JSON_TOKEN_NONE)
                    result.type = PX_JSON_TOKEN_UNSIGNED;
            break;

            case PX_ASCII_MINUS:
                if (result.type == PX_JSON_TOKEN_NONE)
                    result.type = PX_JSON_TOKEN_INTEGER;
            break;

            case PX_ASCII_POINT:
            case PX_ASCII_LOWER_E:
            case PX_ASCII_UPPER_E:
                result.type = PX_JSON_TOKEN_FLOATING;
            break;

            default: break;
        }

        offset += 1;
        byte    = pxReaderPeek(reader, offset);
    }

    PxFormatOptions options =
        pxFormatOptions(10, PX_FORMAT_FLAG_LEADING_PLUS);

    PxString8 string = pxReaderPeekString(reader, arena, offset);

    result.string = string;
    result.length = string.length;

    switch (result.type) {
        case PX_JSON_TOKEN_UNSIGNED: {
            if (pxUnsigFromString8(&result.uvalue, options, string) != 0)
                return result;
        } break;

        case PX_JSON_TOKEN_INTEGER: {
            if (pxIntFromString8(&result.ivalue, options, string) != 0)
                return result;
        } break;

        case PX_JSON_TOKEN_FLOATING: {
            if (1 /* pxFloatFromString8(&result.fvalue, options, string) != 0 */)
                return result;
        } break;

        default: break;
    }

    PxString8 error = pxString8Copy(arena,
        pxStr8("Invalid number, syntactic or overflow"));

    return pxJsonTokenError(string, error);
}

PxJsonToken
pxJsonPeekWord(PxReader* reader, PxArena* arena)
{
    pxint offset = 0;
    pxu8  byte   = pxReaderPeek(reader, offset);

    if (pxAsciiIsLetter(byte) == 0) {
        PxString8 error = pxString8Copy(arena,
            pxStr8("Invalid key word, expected opening letter"));

        PxString8 string = pxString8FromUnicode(arena, byte);

        return pxJsonTokenError(string, error);
    }

    do {
        offset += 1;
        byte    = pxReaderPeek(reader, offset);
    } while (pxAsciiIsLetter(byte) != 0 || pxAsciiIsDigit(byte, 10) != 0);

    PxString8 string = pxReaderPeekString(reader, arena, offset);

    if (pxString8IsEqual(string, pxStr8("true")) != 0)
        return pxJsonTokenBoolean(string, 1);

    if (pxString8IsEqual(string, pxStr8("false")) != 0)
        return pxJsonTokenBoolean(string, 0);

    if (pxString8IsEqual(string, pxStr8("null")) != 0)
        return pxJsonTokenNull(string);

    PxString8 error = pxString8Copy(arena, pxStr8("Invalid key word"));

    return pxJsonTokenError(string, error);
}

PxJsonToken
pxJsonNext(PxReader* reader, PxArena* arena)
{
    PxJsonToken result = pxJsonTokenNone();

    pxu8 byte = pxJsonSkipSpaces(reader);

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
        PxString8 error  = pxString8Copy(arena, pxStr8("Unkown symbol"));
        PxString8 string = pxString8FromUnicode(arena, byte);

        result = pxJsonTokenError(string, error);
    } else
        pxReaderDrop(reader, result.length);

    return result;
}

pxu8
pxJsonSkipSpaces(PxReader* reader)
{
    pxint offset = 0;
    pxu8  byte   = pxReaderPeek(reader, 0);

    while (pxAsciiIsSpace(byte) != 0) {
        offset += 1;
        byte    = pxReaderDrop(reader, 1);
    }

    return byte;
}

#endif // PX_JSON_TOKEN_C
