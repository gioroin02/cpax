#ifndef PX_CORE_FORMAT_MEMORY32_H
#define PX_CORE_FORMAT_MEMORY32_H

#include "config.h"

pxiword
pxMemory32WriteUnsigned8(pxu32* memory, pxiword length, pxuword radix, PxFormatFlag flags, pxu8 value);

pxiword
pxMemory32WriteUnsigned16(pxu32* memory, pxiword length, pxuword radix, PxFormatFlag flags, pxu16 value);

pxiword
pxMemory32WriteUnsigned32(pxu32* memory, pxiword length, pxuword radix, PxFormatFlag flags, pxu32 value);

pxiword
pxMemory32WriteUnsigned64(pxu32* memory, pxiword length, pxuword radix, PxFormatFlag flags, pxu64 value);

pxiword
pxMemory32WriteUnsigned(pxu32* memory, pxiword length, pxuword radix, PxFormatFlag flags, pxuword value);

pxiword
pxMemory32WriteInteger8(pxu32* memory, pxiword length, pxuword radix, PxFormatFlag flags, pxi8 value);

pxiword
pxMemory32WriteInteger16(pxu32* memory, pxiword length, pxuword radix, PxFormatFlag flags, pxi16 value);

pxiword
pxMemory32WriteInteger32(pxu32* memory, pxiword length, pxuword radix, PxFormatFlag flags, pxi32 value);

pxiword
pxMemory32WriteInteger64(pxu32* memory, pxiword length, pxuword radix, PxFormatFlag flags, pxi64 value);

pxiword
pxMemory32WriteInteger(pxu32* memory, pxiword length, pxuword radix, PxFormatFlag flags, pxiword value);

#endif // PX_CORE_FORMAT_MEMORY32_H
