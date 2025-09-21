#ifndef PX_CORE_CONSOLE_ESCAPE_H
#define PX_CORE_CONSOLE_ESCAPE_H

#include "import.h"

#define PX_CONSOLE_ESC_GROUPS pxas(pxiword, 5)
#define PX_CONSOLE_ESC_VALUES pxas(pxiword, 5)

typedef enum PxConsoleEscFlag
{
    PX_CONSOLE_ESC_FLAG_NONE = 0x0,
    PX_CONSOLE_ESC_FLAG_CSI  = 0x1,
    PX_CONSOLE_ESC_FLAG_PRIV = 0x2,
}
PxConsoleEscFlag;

typedef struct PxConsoleEscGroup
{
    pxuword items[PX_CONSOLE_ESC_VALUES];
    pxiword size;
}
PxConsoleEscGroup;

typedef struct PxConsoleEscSeqnc
{
    PxConsoleEscGroup items[PX_CONSOLE_ESC_GROUPS];
    pxiword           size;

    pxu8 func;

    PxConsoleEscFlag flags;
}
PxConsoleEscSeqnc;

/* Group */

PxConsoleEscGroup
pxConsoleEscGroupMake(pxuword* values, pxiword length);

pxb8
pxConsoleEscGroupInsert(PxConsoleEscGroup* self, pxuword value);

pxb8
pxConsoleEscGroupFromString8(PxString8 string, PxConsoleEscGroup* value);

/* Sequence */

PxConsoleEscSeqnc
pxConsoleEscSeqncMake(PxConsoleEscGroup* values, pxiword length);

pxb8
pxConsoleEscSeqncInsert(PxConsoleEscSeqnc* self, PxConsoleEscGroup value);

pxb8
pxConsoleEscSeqncRead(PxConsoleEscSeqnc* self, pxiword group, pxiword index, pxuword* value);

pxuword
pxConsoleEscSeqncReadOr(PxConsoleEscSeqnc* self, pxiword group, pxiword index, pxuword value);

pxb8
pxConsoleEscSeqncFromString8(PxString8 string, PxConsoleEscSeqnc* value);

#endif // PX_CORE_CONSOLE_ESCAPE_H
