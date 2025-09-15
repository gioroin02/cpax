#ifndef PX_CORE_FORMAT_MEMORY16_H
#define PX_CORE_FORMAT_MEMORY16_H

#include "config.h"

pxiword
pxMemory16WriteUnsigned8(pxu16* memory, pxiword length, pxuword radix, PxFormatFlag flags, pxu8 value);

pxiword
pxMemory16WriteUnsigned16(pxu16* memory, pxiword length, pxuword radix, PxFormatFlag flags, pxu16 value);

pxiword
pxMemory16WriteUnsigned32(pxu16* memory, pxiword length, pxuword radix, PxFormatFlag flags, pxu32 value);

pxiword
pxMemory16WriteUnsigned64(pxu16* memory, pxiword length, pxuword radix, PxFormatFlag flags, pxu64 value);

pxiword
pxMemory16WriteUnsigned(pxu16* memory, pxiword length, pxuword radix, PxFormatFlag flags, pxuword value);

pxiword
pxMemory16WriteInteger8(pxu16* memory, pxiword length, pxuword radix, PxFormatFlag flags, pxi8 value);

pxiword
pxMemory16WriteInteger16(pxu16* memory, pxiword length, pxuword radix, PxFormatFlag flags, pxi16 value);

pxiword
pxMemory16WriteInteger32(pxu16* memory, pxiword length, pxuword radix, PxFormatFlag flags, pxi32 value);

pxiword
pxMemory16WriteInteger64(pxu16* memory, pxiword length, pxuword radix, PxFormatFlag flags, pxi64 value);

pxiword
pxMemory16WriteInteger(pxu16* memory, pxiword length, pxuword radix, PxFormatFlag flags, pxiword value);

#endif // PX_CORE_FORMAT_MEMORY16_H
