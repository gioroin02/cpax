#ifndef PX_BASE_MEMORY_H
#define PX_BASE_MEMORY_H

#include "number.h"

#define PX_MEMORY_KB px_as(pxint, 1000)
#define PX_MEMORY_MB px_as(pxint, 1000 * 1000)
#define PX_MEMORY_GB px_as(pxint, 1000 * 1000 * 1000)

#define PX_MEMORY_KIB px_as(pxint, 1024)
#define PX_MEMORY_MIB px_as(pxint, 1024 * 1024)
#define PX_MEMORY_GIB px_as(pxint, 1024 * 1024 * 1024)

void*
pxMemoryZero(void* memory, pxint length, pxint stride);

void*
pxMemoryFlip(void* memory, pxint length, pxint stride);

void*
pxMemoryCopy(void* memory, void* value, pxint length, pxint stride);

void*
pxMemoryCopyFlipped(void* memory, void* value, pxint length, pxint stride);

void*
pxMemoryCopyBack(void* memory, pxint length, pxint offset, pxint stride);

void*
pxMemoryCopyForw(void* memory, pxint length, pxint offset, pxint stride);

pxb8
pxMemoryIsEqual(void* memory, void* value, pxint length, pxint stride);

#endif // PX_BASE_MEMORY_H
