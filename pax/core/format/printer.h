#ifndef PX_CORE_FORMAT_PRINTER_H
#define PX_CORE_FORMAT_PRINTER_H

#include "unsigned.h"
#include "integer.h"
#include "boolean.h"

#define pxBuffer8PrintVargs(self, format, ...) pxBuffer8PrintFormat(self, pxs8(format), \
    pxvargs(PxPrintCmd, __VA_ARGS__), pxvargslen(PxPrintCmd, __VA_ARGS__))

typedef enum PxPrintCmdType
{
    PX_PRINT_CMD_NONE,

    PX_PRINT_CMD_STRING_8,
    PX_PRINT_CMD_STRING_16,
    PX_PRINT_CMD_STRING_32,

    PX_PRINT_CMD_UNICODE,

    PX_PRINT_CMD_UNSIGNED,
    PX_PRINT_CMD_INTEGER,
    PX_PRINT_CMD_FLOATING,
    PX_PRINT_CMD_BOOLEAN,
}
PxPrintCmdType;

typedef struct
{
    PxPrintCmdType type;

    PxFormatRadix radix;
    PxFormatFlag  flags;

    union
    {
        PxString8  string_8;
        PxString16 string_16;
        PxString32 string_32;

        pxi32 unicode;

        pxuword unsigned_word;
        pxiword integer_word;
        pxfword floating_word;
        pxbword boolean_word;
    };
}
PxPrintCmd;

PxPrintCmd
pxPrintCmdString8(PxString8 value);

PxPrintCmd
pxPrintCmdString16(PxString16 value);

PxPrintCmd
pxPrintCmdString32(PxString32 value);

PxPrintCmd
pxPrintCmdUnicode(pxi32 value);

PxPrintCmd
pxPrintCmdUnsigned(pxuword value);

PxPrintCmd
pxPrintCmdInteger(pxiword value);

PxPrintCmd
pxPrintCmdFloating(pxfword value);

PxPrintCmd
pxPrintCmdBoolean(pxbword value);

pxb8
pxBuffer8PrintHead(PxBuffer8* self, PxPrintCmd value);

pxb8
pxBuffer8PrintTail(PxBuffer8* self, PxPrintCmd value);

pxb8
pxBuffer8PrintList(PxBuffer8* self, PxPrintCmd* values, pxiword length);

pxb8
pxBuffer8PrintFormat(PxBuffer8* self, PxString8 format, PxPrintCmd* values, pxiword length);

#endif // PX_CORE_FORMAT_PRINTER_H
