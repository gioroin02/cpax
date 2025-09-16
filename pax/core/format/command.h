#ifndef PX_CORE_STREAM_COMMAND_H
#define PX_CORE_STREAM_COMMAND_H

#include "writer.h"

#define pxWriterFormatVargs(self, arena, format, ...) pxWriterFormat(self, arena, pxs8(format), \
    0, pxvargslen(PxFormatCmd, __VA_ARGS__), pxvargs(PxFormatCmd, __VA_ARGS__))

typedef enum PxFormatCmdType
{
    PX_FORMAT_CMD_NONE,

    PX_FORMAT_CMD_STRING_8,
    PX_FORMAT_CMD_STRING_16,
    PX_FORMAT_CMD_STRING_32,

    PX_FORMAT_CMD_UNICODE,

    PX_FORMAT_CMD_UNSIGNED,
    PX_FORMAT_CMD_INTEGER,
    PX_FORMAT_CMD_FLOATING,
    PX_FORMAT_CMD_BOOLEAN,

    PX_FORMAT_CMD_DELEGATE,
}
PxFormatCmdType;

typedef struct PxFormatCmdUnsigned
{
    PxFormatRadix radix;
    PxFormatFlag  flags;
    pxuword       value;
}
PxFormatCmdUnsigned;

typedef struct PxFormatCmdInteger
{
    PxFormatRadix radix;
    PxFormatFlag  flags;
    pxiword       value;
}
PxFormatCmdInteger;

typedef struct PxFormatCmdFloating
{
    PxFormatRadix radix;
    PxFormatFlag  flags;
    pxfword       value;
}
PxFormatCmdFloating;

typedef struct PxFormatCmdBoolean
{
    PxFormatFlag flags;
    pxbword      value;
}
PxFormatCmdBoolean;

typedef struct PxFormatCmdDelegate
{
    void* ctxt;
    void* proc;
}
PxFormatCmdDelegate;

typedef struct PxFormatCmd
{
    PxFormatCmdType type;

    union
    {
        PxString8  string_8;
        PxString16 string_16;
        PxString32 string_32;

        pxi32 unicode;

        PxFormatCmdUnsigned unsigned_word;
        PxFormatCmdInteger  integer_word;
        PxFormatCmdFloating floating_word;
        PxFormatCmdBoolean  boolean_word;

        PxFormatCmdDelegate delegate;
    };
}
PxFormatCmd;

typedef pxiword (PxOutputFormatProc) (PxOutput*, PxArena*, void*);

/* Commands */

PxFormatCmd
pxFormatCmdString8(PxString8 value);

PxFormatCmd
pxFormatCmdString16(PxString16 value);

PxFormatCmd
pxFormatCmdString32(PxString32 value);

PxFormatCmd
pxFormatCmdUnicode(pxi32 value);

PxFormatCmd
pxFormatCmdUnsigned(pxuword value, PxFormatRadix radix, PxFormatFlag flags);

PxFormatCmd
pxFormatCmdInteger(pxiword value, PxFormatRadix radix, PxFormatFlag flags);

PxFormatCmd
pxFormatCmdFloating(pxfword value, PxFormatRadix radix, PxFormatFlag flags);

PxFormatCmd
pxFormatCmdBoolean(pxbword value, PxFormatFlag flags);

PxFormatCmd
pxFormatCmdDelegate(void* ctxt, void* proc);

/* Writer */

pxiword
pxWriterFormatCmd(PxOutput* self, PxArena* arena, PxFormatCmd value);

pxiword
pxWriterFormatList(PxOutput* self, PxArena* arena, pxiword start, pxiword stop, PxFormatCmd* list);

pxiword
pxWriterFormat(PxOutput* self, PxArena* arena, PxString8 format, pxiword start, pxiword stop, PxFormatCmd* list);

#endif // PX_CORE_STREAM_COMMAND_H
