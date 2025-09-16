#ifndef PX_CORE_FORMAT_UNSIGNED_H
#define PX_CORE_FORMAT_UNSIGNED_H

#include "config.h"

pxiword
pxUnsignedDigits(pxuword value, PxFormatRadix radix, PxFormatFlag flags);

/* Memory */

pxiword
pxMemory8WriteUnsigned(pxu8* memory, pxiword length,
    pxuword value, PxFormatRadix radix, PxFormatFlag flags);

pxiword
pxMemory8ReadUnsigned(pxu8* memory, pxiword length,
    pxuword* value, PxFormatRadix radix, PxFormatFlag flags);

pxiword
pxMemory16WriteUnsigned(pxu16* memory, pxiword length,
    pxuword value, PxFormatRadix radix, PxFormatFlag flags);

pxiword
pxMemory16ReadUnsigned(pxu16* memory, pxiword length,
    pxuword* value, PxFormatRadix radix, PxFormatFlag flags);

pxiword
pxMemory32WriteUnsigned(pxu32* memory, pxiword length,
    pxuword value, PxFormatRadix radix, PxFormatFlag flags);

pxiword
pxMemory32ReadUnsigned(pxu32* memory, pxiword length,
    pxuword* value, PxFormatRadix radix, PxFormatFlag flags);

/* String */

PxString8
pxString8FromUnsigned(PxArena* arena, pxuword value, PxFormatRadix radix, PxFormatFlag flags);

pxb8
pxUnsignedFromString8(PxString8 string, pxuword* value, PxFormatRadix radix, PxFormatFlag flags);

PxString16
pxString16FromUnsigned(PxArena* arena, pxuword value, PxFormatRadix radix, PxFormatFlag flags);

pxb8
pxUnsignedFromString16(PxString16 string, pxuword* value, PxFormatRadix radix, PxFormatFlag flags);

PxString32
pxString32FromUnsigned(PxArena* arena, pxuword value, PxFormatRadix radix, PxFormatFlag flags);

pxb8
pxUnsignedFromString32(PxString32 string, pxuword* value, PxFormatRadix radix, PxFormatFlag flags);

/* Buffer */ /*

pxiword
pxBuffer8WriteUnsignedHead(PxBuffer8* self, pxuword value, PxFormatRadix radix, PxFormatFlag flags);

pxiword
pxBuffer8WriteUnsignedTail(PxBuffer8* self, pxuword value, PxFormatRadix radix, PxFormatFlag flags);

pxiword
pxBuffer16WriteUnsignedHead(PxBuffer16* self, pxuword value, PxFormatRadix radix, PxFormatFlag flags);

pxiword
pxBuffer16WriteUnsignedTail(PxBuffer16* self, pxuword value, PxFormatRadix radix, PxFormatFlag flags);

pxiword
pxBuffer32WriteUnsignedHead(PxBuffer32* self, pxuword value, PxFormatRadix radix, PxFormatFlag flags);

pxiword
pxBuffer32WriteUnsignedTail(PxBuffer32* self, pxuword value, PxFormatRadix radix, PxFormatFlag flags);

pxiword
pxBuffer8ReadUnsignedTail(PxBuffer8* self, pxiword length,
    pxuword* value, PxFormatRadix radix, PxFormatFlag flags);

pxiword
pxBuffer16ReadUnsignedHead(PxBuffer16* self, pxiword length,
    pxuword* value, PxFormatRadix radix, PxFormatFlag flags);

pxiword
pxBuffer16ReadUnsignedTail(PxBuffer16* self, pxiword length,
    pxuword* value, PxFormatRadix radix, PxFormatFlag flags);

pxiword
pxBuffer32ReadUnsignedHead(PxBuffer32* memory, pxiword length,
    pxuword* value, PxFormatRadix radix, PxFormatFlag flags);

pxiword
pxBuffer32ReadUnsignedTail(PxBuffer32* memory, pxiword length,
    pxuword* value, PxFormatRadix radix, PxFormatFlag flags);

pxiword
pxBuffer8ReadUnsignedHead(PxBuffer8* self, pxiword length,
    pxuword* value, PxFormatRadix radix, PxFormatFlag flags);

pxiword
pxBuffer8ReadUnsignedTail(PxBuffer8* self, pxiword length,
    pxuword* value, PxFormatRadix radix, PxFormatFlag flags);

pxiword
pxBuffer16ReadUnsignedHead(PxBuffer16* self, pxiword length,
    pxuword* value, PxFormatRadix radix, PxFormatFlag flags);

pxiword
pxBuffer16ReadUnsignedTail(PxBuffer16* self, pxiword length,
    pxuword* value, PxFormatRadix radix, PxFormatFlag flags);

pxiword
pxBuffer32ReadUnsignedHead(PxBuffer32* memory, pxiword length,
    pxuword* value, PxFormatRadix radix, PxFormatFlag flags);

pxiword
pxBuffer32ReadUnsignedTail(PxBuffer32* memory, pxiword length,
    pxuword* value, PxFormatRadix radix, PxFormatFlag flags);

*/

#endif // PX_CORE_FORMAT_UNSIGNED_H
