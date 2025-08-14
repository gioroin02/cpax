#ifndef PAX_BASE_MEMORY_C
#define PAX_BASE_MEMORY_C

#include "memory.h"

void*
mem_zero(void* memory, Int length, Int stride)
{
    if (length <= 0 || stride <= 0) return memory;

    for (Int i = 0; i < length * stride; i += 1)
        pax_as(nat8*, memory)[i] = 0;

    return memory;
}

void*
mem_flip(void* memory, Int length, Int stride)
{
    if (length <= 0 || stride <= 0) return memory;

    Int l = 0;
    Int r = stride * (length - 1);

    for (; l < r; l += stride, r -= stride) {
        for (Int i = 0; i < stride; i += 1) {
            nat8 left  = pax_as(nat8*, memory)[l + i];
            nat8 right = pax_as(nat8*, memory)[r + i];

            pax_as(nat8*, memory)[l + i] = right;
            pax_as(nat8*, memory)[r + i] = left;
        }
    }

    return memory;
}

void*
mem_copy(void* memory, void* value, Int length, Int stride)
{
    if (length <= 0 || stride <= 0) return memory;

    for (Int i = 0; i < length * stride; i += 1)
        pax_as(nat8*, memory)[i] = pax_as(nat8*, value)[i];

    return memory;
}

void*
mem_copy_flipped(void* memory, void* value, Int length, Int stride)
{
    if (length <= 0 || stride <= 0) return memory;

    for (Int i = 0; i < length; i += 1) {
        Int k = (length - i - 1);

        for (Int j = 0; j < stride; j += 1) {
            pax_as(nat8*, memory)[i * stride + j] =
                pax_as(nat8*, value)[k * stride + j];
        }
    }

    return memory;
}

void*
mem_copy_back(void* memory, Int length, Int offset, Int stride)
{
    if (length <= 0 || stride <= 0 || offset <= 0)
        return memory;

    nat8* result = pax_as(nat8*, memory) - offset * stride;

    for (Int i = 0; i < length * stride; i += 1)
        result[i] = pax_as(nat8*, memory)[i];

    return result;
}

void*
mem_copy_forw(void* memory, Int length, Int offset, Int stride)
{
    if (length <= 0 || stride <= 0 || offset <= 0)
        return memory;

    nat8* result = pax_as(nat8*, memory) + offset * stride;

    for (Int i = length * stride; i > 0; i -= 1)
        result[i - 1] = pax_as(nat8*, memory)[i - 1];

    return result;
}

bool8
mem_is_equal(void* memory, void* value, Int length, Int stride)
{
    if (length <= 0 || stride <= 0) return 0;

    for (Int i = 0; i < length * stride; i += 1) {
        if (pax_as(nat8*, memory)[i] != pax_as(nat8*, value)[i])
            return 0;
    }

    return 1;
}

#endif // PAX_BASE_MEMORY_C
