#ifndef PX_BASE_MEMORY_C
#define PX_BASE_MEMORY_C

#include "memory.h"

void*
pxMemoryZero(void* memory, pxint length, pxint stride)
{
    if (length <= 0 || stride <= 0) return memory;

    for (pxint i = 0; i < length * stride; i += 1)
        pxCast(pxword8*, memory)[i] = 0;

    return memory;
}

void*
pxMemoryFlip(void* memory, pxint length, pxint stride)
{
    if (length <= 0 || stride <= 0) return memory;

    pxint l = 0;
    pxint r = stride * (length - 1);

    for (; l < r; l += stride, r -= stride) {
        for (pxint i = 0; i < stride; i += 1) {
            pxword8 left  = pxCast(pxword8*, memory)[l + i];
            pxword8 right = pxCast(pxword8*, memory)[r + i];

            pxCast(pxword8*, memory)[l + i] = right;
            pxCast(pxword8*, memory)[r + i] = left;
        }
    }

    return memory;
}

void*
pxMemoryCopy(void* memory, void* value, pxint length, pxint stride)
{
    if (length <= 0 || stride <= 0) return memory;

    for (pxint i = 0; i < length * stride; i += 1)
        pxCast(pxword8*, memory)[i] = pxCast(pxword8*, value)[i];

    return memory;
}

void*
pxMemoryCopyFlipped(void* memory, void* value, pxint length, pxint stride)
{
    if (length <= 0 || stride <= 0) return memory;

    for (pxint i = 0; i < length; i += 1) {
        pxint k = (length - i - 1);

        for (pxint j = 0; j < stride; j += 1) {
            pxCast(pxword8*, memory)[i * stride + j] =
                pxCast(pxword8*, value)[k * stride + j];
        }
    }

    return memory;
}

void*
pxMemoryCopyBack(void* memory, pxint length, pxint offset, pxint stride)
{
    if (length <= 0 || stride <= 0 || offset <= 0)
        return memory;

    pxword8* result = pxCast(pxword8*, memory) - offset * stride;

    for (pxint i = 0; i < length * stride; i += 1)
        result[i] = pxCast(pxword8*, memory)[i];

    return result;
}

void*
pxMemoryCopyForw(void* memory, pxint length, pxint offset, pxint stride)
{
    if (length <= 0 || stride <= 0 || offset <= 0)
        return memory;

    pxword8* result = pxCast(pxword8*, memory) + offset * stride;

    for (pxint i = length * stride; i > 0; i -= 1)
        result[i - 1] = pxCast(pxword8*, memory)[i - 1];

    return result;
}

pxbool8
pxMemoryIsEqual(void* memory, void* value, pxint length, pxint stride)
{
    if (length <= 0 || stride <= 0) return 0;

    for (pxint i = 0; i < length * stride; i += 1) {
        if (pxCast(pxword8*, memory)[i] != pxCast(pxword8*, value)[i])
            return 0;
    }

    return 1;
}

#endif // PX_BASE_MEMORY_C
