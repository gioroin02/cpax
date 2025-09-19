#ifndef PX_CORE_FORMAT_INTEGER_H
#define PX_CORE_FORMAT_INTEGER_H

#include "config.h"

pxiword
pxIntegerDigits(pxiword value, PxFmtRadix radix, PxFmtFlag flags);

/* Memory */

pxiword
pxMemory8WriteInteger(pxu8* memory, pxiword length, pxiword value, PxFmtRadix radix, PxFmtFlag flags);

pxiword
pxMemory8ReadInteger(pxu8* memory, pxiword length, pxiword* value, PxFmtRadix radix, PxFmtFlag flags);

pxiword
pxMemory16WriteInteger(pxu16* memory, pxiword length, pxiword value, PxFmtRadix radix, PxFmtFlag flags);

pxiword
pxMemory16ReadInteger(pxu16* memory, pxiword length, pxiword* value, PxFmtRadix radix, PxFmtFlag flags);

pxiword
pxMemory32WriteInteger(pxu32* memory, pxiword length, pxiword value, PxFmtRadix radix, PxFmtFlag flags);

pxiword
pxMemory32ReadInteger(pxu32* memory, pxiword length, pxiword* value, PxFmtRadix radix, PxFmtFlag flags);

/* String */

PxString8
pxString8FromInteger(PxArena* arena, pxiword value, PxFmtRadix radix, PxFmtFlag flags);

pxb8
pxIntegerFromString8(PxString8 string, pxiword* value, PxFmtRadix radix, PxFmtFlag flags);

PxString16
pxString16FromInteger(PxArena* arena, pxiword value, PxFmtRadix radix, PxFmtFlag flags);

pxb8
pxIntegerFromString16(PxString16 string, pxiword* value, PxFmtRadix radix, PxFmtFlag flags);

PxString32
pxString32FromInteger(PxArena* arena, pxiword value, PxFmtRadix radix, PxFmtFlag flags);

pxb8
pxIntegerFromString32(PxString32 string, pxiword* value, PxFmtRadix radix, PxFmtFlag flags);

/* Buffer */

pxiword
pxBuffer8WriteIntegerHead(PxBuffer8* self, pxiword value, PxFmtRadix radix, PxFmtFlag flags);

pxiword
pxBuffer8WriteIntegerTail(PxBuffer8* self, pxiword value, PxFmtRadix radix, PxFmtFlag flags);

pxiword
pxBuffer16WriteIntegerHead(PxBuffer16* self, pxiword value, PxFmtRadix radix, PxFmtFlag flags);

pxiword
pxBuffer16WriteIntegerTail(PxBuffer16* self, pxiword value, PxFmtRadix radix, PxFmtFlag flags);

pxiword
pxBuffer32WriteIntegerHead(PxBuffer32* self, pxiword value, PxFmtRadix radix, PxFmtFlag flags);

pxiword
pxBuffer32WriteIntegerTail(PxBuffer32* self, pxiword value, PxFmtRadix radix, PxFmtFlag flags);

/* Writer */

pxiword
pxWriterNextInteger(PxWriter* self, pxiword value, PxFmtRadix radix, PxFmtFlag flags);

#endif // PX_CORE_FORMAT_INTEGER_H
