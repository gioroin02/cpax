#ifndef PX_CORE_FORMAT_BUILDER_H
#define PX_CORE_FORMAT_BUILDER_H

#include "string8.h"
#include "string16.h"
#include "string32.h"

#define pxBuilderBuild(self, format, ...) \
    pxBuilderFormat(self, pxs8(format), 0, pxSizeVargs(PxBuilderCmd, __VA_ARGS__), pxVargs(PxBuilderCmd, __VA_ARGS__))

typedef enum PxBuilderCmdType
{
    PX_BUILDER_CMD_NONE,

    PX_BUILDER_CMD_UNSIGNED_8,
    PX_BUILDER_CMD_UNSIGNED_16,
    PX_BUILDER_CMD_UNSIGNED_32,
    PX_BUILDER_CMD_UNSIGNED_64,
    PX_BUILDER_CMD_UNSIGNED,

    PX_BUILDER_CMD_INTEGER_8,
    PX_BUILDER_CMD_INTEGER_16,
    PX_BUILDER_CMD_INTEGER_32,
    PX_BUILDER_CMD_INTEGER_64,
    PX_BUILDER_CMD_INTEGER,

    PX_BUILDER_CMD_BOOLEAN_8,
    PX_BUILDER_CMD_BOOLEAN_16,
    PX_BUILDER_CMD_BOOLEAN_32,
    PX_BUILDER_CMD_BOOLEAN_64,
    PX_BUILDER_CMD_BOOLEAN,

    PX_BUILDER_CMD_UNICODE,

    PX_BUILDER_CMD_STRING_8,
    PX_BUILDER_CMD_STRING_16,
    PX_BUILDER_CMD_STRING_32,
}
PxBuilderCmdType;

typedef struct PxBuilderCmdUnsigned8
{
    pxuword        radix;
    PxFormatOption options;
    pxu8           value;
}
PxBuilderCmdUnsigned8;

typedef struct PxBuilderCmdUnsigned16
{
    pxuword        radix;
    PxFormatOption options;
    pxu16          value;
}
PxBuilderCmdUnsigned16;

typedef struct PxBuilderCmdUnsigned32
{
    pxuword        radix;
    PxFormatOption options;
    pxu32          value;
}
PxBuilderCmdUnsigned32;

typedef struct PxBuilderCmdUnsigned64
{
    pxuword        radix;
    PxFormatOption options;
    pxu64          value;
}
PxBuilderCmdUnsigned64;

typedef struct PxBuilderCmdUnsigned
{
    pxuword        radix;
    PxFormatOption options;
    pxuword        value;
}
PxBuilderCmdUnsigned;

typedef struct PxBuilderCmdInteger8
{
    pxuword        radix;
    PxFormatOption options;
    pxi8           value;
}
PxBuilderCmdInteger8;

typedef struct PxBuilderCmdInteger16
{
    pxuword        radix;
    PxFormatOption options;
    pxi16          value;
}
PxBuilderCmdInteger16;

typedef struct PxBuilderCmdInteger32
{
    pxuword        radix;
    PxFormatOption options;
    pxi32          value;
}
PxBuilderCmdInteger32;

typedef struct PxBuilderCmdInteger64
{
    pxuword        radix;
    PxFormatOption options;
    pxi64          value;
}
PxBuilderCmdInteger64;

typedef struct PxBuilderCmdInteger
{
    pxuword        radix;
    PxFormatOption options;
    pxiword        value;
}
PxBuilderCmdInteger;

typedef struct PxBuilderCmd
{
    PxBuilderCmdType type;

    union
    {
        PxBuilderCmdUnsigned8  unsigned_8;
        PxBuilderCmdUnsigned16 unsigned_16;
        PxBuilderCmdUnsigned32 unsigned_32;
        PxBuilderCmdUnsigned64 unsigned_64;
        PxBuilderCmdUnsigned   unsigned_word;

        PxBuilderCmdInteger8  integer_8;
        PxBuilderCmdInteger16 integer_16;
        PxBuilderCmdInteger32 integer_32;
        PxBuilderCmdInteger64 integer_64;
        PxBuilderCmdInteger   integer_word;

        pxb8    boolean_8;
        pxb16   boolean_16;
        pxb32   boolean_32;
        pxb64   boolean_64;
        pxbword boolean_word;

        pxi32 unicode;

        PxString8  string_8;
        PxString16 string_16;
        PxString32 string_32;
    };
}
PxBuilderCmd;

typedef struct PxBuilder
{
    pxu8*   memory;
    pxiword length;
    pxiword size;
}
PxBuilder;

/* Commands */

PxBuilderCmd
pxBuilderCmdUnsigned8(pxuword radix, PxFormatOption options, pxu8 value);

PxBuilderCmd
pxBuilderCmdUnsigned16(pxuword radix, PxFormatOption options, pxu16 value);

PxBuilderCmd
pxBuilderCmdUnsigned32(pxuword radix, PxFormatOption options, pxu32 value);

PxBuilderCmd
pxBuilderCmdUnsigned64(pxuword radix, PxFormatOption options, pxu64 value);

PxBuilderCmd
pxBuilderCmdUnsigned(pxuword radix, PxFormatOption options, pxuword value);

PxBuilderCmd
pxBuilderCmdInteger8(pxuword radix, PxFormatOption options, pxi8 value);

PxBuilderCmd
pxBuilderCmdInteger16(pxuword radix, PxFormatOption options, pxi16 value);

PxBuilderCmd
pxBuilderCmdInteger32(pxuword radix, PxFormatOption options, pxi32 value);

PxBuilderCmd
pxBuilderCmdInteger64(pxuword radix, PxFormatOption options, pxi64 value);

PxBuilderCmd
pxBuilderCmdInteger(pxuword radix, PxFormatOption options, pxiword value);

PxBuilderCmd
pxbuilderCmdBoolean8(pxb8 value);

PxBuilderCmd
pxbuilderCmdBoolean16(pxb16 value);

PxBuilderCmd
pxbuilderCmdBoolean32(pxb32 value);

PxBuilderCmd
pxbuilderCmdBoolean64(pxb64 value);

PxBuilderCmd
pxbuilderCmdBoolean(pxbword value);

PxBuilderCmd
pxBuilderCmdUnicode(pxi32 value);

PxBuilderCmd
pxBuilderCmdString8(PxString8 value);

PxBuilderCmd
pxBuilderCmdString16(PxString16 value);

PxBuilderCmd
pxBuilderCmdString32(PxString32 value);

/* Builder */

PxBuilder
pxBuilderMake(pxu8* memory, pxiword length);

PxBuilder
pxBuilderReserve(PxArena* arena, pxiword length);

void
pxBuilderClear(PxBuilder* self);

pxiword
pxBuilderFormat(PxBuilder* self, PxString8 format, pxiword start, pxiword stop, PxBuilderCmd* list);

pxiword
pxBuilderChain(PxBuilder* self, pxiword start, pxiword stop, PxBuilderCmd* list);

pxiword
pxBuilderCommand(PxBuilder* self, PxBuilderCmd command);

PxString8
pxString8FromBuilder(PxArena* arena, PxBuilder* builder);

PxString16
pxString16FromBuilder(PxArena* arena, PxBuilder* builder);

PxString32
pxString32FromBuilder(PxArena* arena, PxBuilder* builder);

#endif // PX_CORE_FORMAT_BUILDER_H
