#ifndef PX_JSON_TOKEN_H
#define PX_JSON_TOKEN_H

#include "import.h"

typedef enum PxJsonTokenType
{
    PX_JSON_TOKEN_NONE,

    PX_JSON_TOKEN_ERROR,

    PX_JSON_TOKEN_OBJECT_OPEN,
    PX_JSON_TOKEN_OBJECT_CLOSE,
    PX_JSON_TOKEN_ARRAY_OPEN,
    PX_JSON_TOKEN_ARRAY_CLOSE,
    PX_JSON_TOKEN_COLON,
    PX_JSON_TOKEN_COMMA,

    PX_JSON_TOKEN_STRING,
    PX_JSON_TOKEN_UNSIGNED,
    PX_JSON_TOKEN_INTEGER,
    PX_JSON_TOKEN_FLOATING,
    PX_JSON_TOKEN_BOOLEAN,
    PX_JSON_TOKEN_NULL,

    PX_JSON_TOKEN_COUNT,
}
PxJsonTokenType;

typedef struct PxJsonToken
{
    PxJsonTokenType type;

    PxString8 string;
    pxint     length;

    union
    {
        PxString8 error;
        pxunsig   uvalue;
        pxint     ivalue;
        pxfloat   fvalue;
        pxbool    bvalue;
    };
}
PxJsonToken;

PxJsonToken
pxJsonTokenNone();

PxJsonToken
pxJsonTokenError(PxString8 string, PxString8 error);

PxJsonToken
pxJsonTokenObjectOpen(PxString8 string);

PxJsonToken
pxJsonTokenObjectClose(PxString8 string);

PxJsonToken
pxJsonTokenArrayOpen(PxString8 string);

PxJsonToken
pxJsonTokenArrayClose(PxString8 string);

PxJsonToken
pxJsonTokenColon(PxString8 string);

PxJsonToken
pxJsonTokenComma(PxString8 string);

PxJsonToken
pxJsonTokenString(PxString8 string);

PxJsonToken
pxJsonTokenUnsigned(PxString8 string, pxunsig value);

PxJsonToken
pxJsonTokenInteger(PxString8 string, pxint value);

PxJsonToken
pxJsonTokenFloating(PxString8 string, pxfloat vlaue);

PxJsonToken
pxJsonTokenBoolean(PxString8 string, pxbool value);

PxJsonToken
pxJsonTokenNull(PxString8 string);

PxJsonToken
pxJsonTokenCount();

PxJsonToken
pxJsonPeek(PxReader* reader, PxArena* arena);

PxJsonToken
pxJsonPeekSymbol(PxReader* reader, PxArena* arena);

PxJsonToken
pxJsonPeekString(PxReader* reader, PxArena* arena);

PxJsonToken
pxJsonPeekNumber(PxReader* reader, PxArena* arena);

PxJsonToken
pxJsonPeekWord(PxReader* reader, PxArena* arena);

PxJsonToken
pxJsonNext(PxReader* reader, PxArena* arena);

pxu8
pxJsonSkipSpaces(PxReader* reader);

#endif // PX_JSON_TOKEN_H
