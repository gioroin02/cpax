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

    PX_BUILDER_CMD_UNSIGNED8,
    PX_BUILDER_CMD_UNSIGNED16,
    PX_BUILDER_CMD_UNSIGNED32,
    PX_BUILDER_CMD_UNSIGNED64,
    PX_BUILDER_CMD_UNSIGNED,

    PX_BUILDER_CMD_INTEGER8,
    PX_BUILDER_CMD_INTEGER16,
    PX_BUILDER_CMD_INTEGER32,
    PX_BUILDER_CMD_INTEGER64,
    PX_BUILDER_CMD_INTEGER,

    PX_BUILDER_CMD_UNICODE,

    PX_BUILDER_CMD_STRING8,
    PX_BUILDER_CMD_STRING16,
    PX_BUILDER_CMD_STRING32,
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
        PxBuilderCmdUnsigned8  u8;
        PxBuilderCmdUnsigned16 u16;
        PxBuilderCmdUnsigned32 u32;
        PxBuilderCmdUnsigned64 u64;
        PxBuilderCmdUnsigned   uword;

        PxBuilderCmdInteger8  i8;
        PxBuilderCmdInteger16 i16;
        PxBuilderCmdInteger32 i32;
        PxBuilderCmdInteger64 i64;
        PxBuilderCmdInteger   iword;

        pxi32 unicode;

        PxString8  string8;
        PxString16 string16;
        PxString32 string32;
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
