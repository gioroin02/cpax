#ifndef PX_BASE_MEMORY_H
#define PX_BASE_MEMORY_H

#include "number.h"

#define PX_MEMORY_KB pxCast(pxint, 1000)
#define PX_MEMORY_MB pxCast(pxint, 1000 * 1000)
#define PX_MEMORY_GB pxCast(pxint, 1000 * 1000 * 1000)

#define PX_MEMORY_KIB pxCast(pxint, 1024)
#define PX_MEMORY_MIB pxCast(pxint, 1024 * 1024)
#define PX_MEMORY_GIB pxCast(pxint, 1024 * 1024 * 1024)

void*
pxMemoryZero(void* memory, pxint amount, pxint stride);

void*
pxMemoryFlip(void* memory, pxint amount, pxint stride);

void*
pxMemoryCopy(void* memory, void* value, pxint amount, pxint stride);

void*
pxMemoryCopyFlipped(void* memory, void* value, pxint amount, pxint stride);

void*
pxMemoryCopyBack(void* memory, pxint amount, pxint offset, pxint stride);

void*
pxMemoryCopyForw(void* memory, pxint amount, pxint offset, pxint stride);

pxb8
pxMemoryIsEqual(void* memory, void* value, pxint amount, pxint stride);

#endif // PX_BASE_MEMORY_H
