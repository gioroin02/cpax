#ifndef PX_CORE_FORMAT_UNSIGNED_H
#define PX_CORE_FORMAT_UNSIGNED_H

#include "config.h"

pxiword
pxUnsignedDigits(pxuword value, PxFmtRadix radix, PxFmtFlag flags);

/* Memory */

pxiword
pxMemory8WriteUnsigned(pxu8* memory, pxiword length, pxuword value, PxFmtRadix radix, PxFmtFlag flags);

pxiword
pxMemory8ReadUnsigned(pxu8* memory, pxiword length, pxuword* value, PxFmtRadix radix, PxFmtFlag flags);

pxiword
pxMemory16WriteUnsigned(pxu16* memory, pxiword length, pxuword value, PxFmtRadix radix, PxFmtFlag flags);

pxiword
pxMemory16ReadUnsigned(pxu16* memory, pxiword length, pxuword* value, PxFmtRadix radix, PxFmtFlag flags);

pxiword
pxMemory32WriteUnsigned(pxu32* memory, pxiword length, pxuword value, PxFmtRadix radix, PxFmtFlag flags);

pxiword
pxMemory32ReadUnsigned(pxu32* memory, pxiword length, pxuword* value, PxFmtRadix radix, PxFmtFlag flags);

/* String */

PxString8
pxString8FromUnsigned(PxArena* arena, pxuword value, PxFmtRadix radix, PxFmtFlag flags);

pxb8
pxUnsignedFromString8(PxString8 string, pxuword* value, PxFmtRadix radix, PxFmtFlag flags);

PxString16
pxString16FromUnsigned(PxArena* arena, pxuword value, PxFmtRadix radix, PxFmtFlag flags);

pxb8
pxUnsignedFromString16(PxString16 string, pxuword* value, PxFmtRadix radix, PxFmtFlag flags);

PxString32
pxString32FromUnsigned(PxArena* arena, pxuword value, PxFmtRadix radix, PxFmtFlag flags);

pxb8
pxUnsignedFromString32(PxString32 string, pxuword* value, PxFmtRadix radix, PxFmtFlag flags);

/* Buffer */

pxiword
pxBuffer8WriteUnsignedHead(PxBuffer8* self, pxuword value, PxFmtRadix radix, PxFmtFlag flags);

pxiword
pxBuffer8WriteUnsignedTail(PxBuffer8* self, pxuword value, PxFmtRadix radix, PxFmtFlag flags);

pxiword
pxBuffer16WriteUnsignedHead(PxBuffer16* self, pxuword value, PxFmtRadix radix, PxFmtFlag flags);

pxiword
pxBuffer16WriteUnsignedTail(PxBuffer16* self, pxuword value, PxFmtRadix radix, PxFmtFlag flags);

pxiword
pxBuffer32WriteUnsignedHead(PxBuffer32* self, pxuword value, PxFmtRadix radix, PxFmtFlag flags);

pxiword
pxBuffer32WriteUnsignedTail(PxBuffer32* self, pxuword value, PxFmtRadix radix, PxFmtFlag flags);

/* Writer */

pxiword
pxWriterNextUnsigned(PxWriter* self, pxuword value, PxFmtRadix radix, PxFmtFlag flags);

#endif // PX_CORE_FORMAT_UNSIGNED_H
