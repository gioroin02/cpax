#ifndef PX_FORMAT_STRING32_H
#define PX_FORMAT_STRING32_H

#include "options.h"

/* String from number */

PxString32
pxString32FromUnsig8(PxArena* arena, PxFormatOptions options, pxu8 value);

PxString32
pxString32FromUnsig16(PxArena* arena, PxFormatOptions options, pxu16 value);

PxString32
pxString32FromUnsig32(PxArena* arena, PxFormatOptions options, pxu32 value);

PxString32
pxString32FromUnsig64(PxArena* arena, PxFormatOptions options, pxu64 value);

PxString32
pxString32FromUnsig(PxArena* arena, PxFormatOptions options, pxunsig value);

PxString32
pxString32FromInt8(PxArena* arena, PxFormatOptions options, pxi8 value);

PxString32
pxString32FromInt16(PxArena* arena, PxFormatOptions options, pxi16 value);

PxString32
pxString32FromInt32(PxArena* arena, PxFormatOptions options, pxi32 value);

PxString32
pxString32FromInt64(PxArena* arena, PxFormatOptions options, pxi64 value);

PxString32
pxString32FromInt(PxArena* arena, PxFormatOptions options, pxint value);

/* Number from string */

pxb8
pxUnsig8FromString32(pxu8* self, PxFormatOptions options, PxString32 string);

pxb8
pxUnsig16FromString32(pxu16* self, PxFormatOptions options, PxString32 string);

pxb8
pxUnsig32FromString32(pxu32* self, PxFormatOptions options, PxString32 string);

pxb8
pxUnsig64FromString32(pxu64* self, PxFormatOptions options, PxString32 string);

pxb8
pxUnsigFromString32(pxunsig* self, PxFormatOptions options, PxString32 string);

pxb8
pxInt8FromString32(pxi8* self, PxFormatOptions options, PxString32 string);

pxb8
pxInt16FromString32(pxi16* self, PxFormatOptions options, PxString32 string);

pxb8
pxInt32FromString32(pxi32* self, PxFormatOptions options, PxString32 string);

pxb8
pxInt64FromString32(pxi64* self, PxFormatOptions options, PxString32 string);

pxb8
pxIntFromString32(pxint* self, PxFormatOptions options, PxString32 string);

#endif // PX_FORMAT_STRING32_H
