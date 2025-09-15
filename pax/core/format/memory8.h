#ifndef PX_CORE_FORMAT_MEMORY8_H
#define PX_CORE_FORMAT_MEMORY8_H

#include "config.h"

pxiword
pxMemory8WriteUnsigned8(pxu8* memory, pxiword length, pxuword radix, PxFormatFlag flags, pxu8 value);

pxiword
pxMemory8WriteUnsigned16(pxu8* memory, pxiword length, pxuword radix, PxFormatFlag flags, pxu16 value);

pxiword
pxMemory8WriteUnsigned32(pxu8* memory, pxiword length, pxuword radix, PxFormatFlag flags, pxu32 value);

pxiword
pxMemory8WriteUnsigned64(pxu8* memory, pxiword length, pxuword radix, PxFormatFlag flags, pxu64 value);

pxiword
pxMemory8WriteUnsigned(pxu8* memory, pxiword length, pxuword radix, PxFormatFlag flags, pxuword value);

pxiword
pxMemory8WriteInteger8(pxu8* memory, pxiword length, pxuword radix, PxFormatFlag flags, pxi8 value);

pxiword
pxMemory8WriteInteger16(pxu8* memory, pxiword length, pxuword radix, PxFormatFlag flags, pxi16 value);

pxiword
pxMemory8WriteInteger32(pxu8* memory, pxiword length, pxuword radix, PxFormatFlag flags, pxi32 value);

pxiword
pxMemory8WriteInteger64(pxu8* memory, pxiword length, pxuword radix, PxFormatFlag flags, pxi64 value);

pxiword
pxMemory8WriteInteger(pxu8* memory, pxiword length, pxuword radix, PxFormatFlag flags, pxiword value);

#endif // PX_CORE_FORMAT_MEMORY8_H
