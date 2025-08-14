#ifndef PAX_BASE_MEMORY_H
#define PAX_BASE_MEMORY_H

#include "number.h"

static const Int MEMORY_KB = pax_as(Int, 1000);
static const Int MEMORY_MB = pax_as(Int, 1000 * 1000);
static const Int MEMORY_GB = pax_as(Int, 1000 * 1000 * 1000);

static const Int MEMORY_KIB = pax_as(Int, 1024);
static const Int MEMORY_MIB = pax_as(Int, 1024 * 1024);
static const Int MEMORY_GIB = pax_as(Int, 1024 * 1024 * 1024);

void*
mem_zero(void* memory, Int length, Int stride);

void*
mem_flip(void* memory, Int length, Int stride);

void*
mem_copy(void* memory, void* value, Int length, Int stride);

void*
mem_copy_flipped(void* memory, void* value, Int length, Int stride);

void*
mem_copy_back(void* memory, Int length, Int offset, Int stride);

void*
mem_copy_forw(void* memory, Int length, Int offset, Int stride);

bool8
mem_is_equal(void* memory, void* value, Int length, Int stride);

#endif // PAX_BASE_MEMORY_H
