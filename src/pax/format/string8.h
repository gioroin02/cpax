#ifndef PX_FORMAT_STRING8_H
#define PX_FORMAT_STRING8_H

#include "options.h"

/* String from number */

PxString8
pxString8FromUnsig8(PxArena* arena, PxFormatOptions options, pxu8 value);

PxString8
pxString8FromUnsig16(PxArena* arena, PxFormatOptions options, pxu16 value);

PxString8
pxString8FromUnsig32(PxArena* arena, PxFormatOptions options, pxu32 value);

PxString8
pxString8FromUnsig64(PxArena* arena, PxFormatOptions options, pxu64 value);

PxString8
pxString8FromUnsig(PxArena* arena, PxFormatOptions options, pxunsig value);

PxString8
pxString8FromInt8(PxArena* arena, PxFormatOptions options, pxi8 value);

PxString8
pxString8FromInt16(PxArena* arena, PxFormatOptions options, pxi16 value);

PxString8
pxString8FromInt32(PxArena* arena, PxFormatOptions options, pxi32 value);

PxString8
pxString8FromInt64(PxArena* arena, PxFormatOptions options, pxi64 value);

PxString8
pxString8FromInt(PxArena* arena, PxFormatOptions options, pxint value);

/* Number from string */

pxb8
pxUnsig8FromString8(pxu8* self, PxFormatOptions options, PxString8 string);

pxb8
pxUnsig16FromString8(pxu16* self, PxFormatOptions options, PxString8 string);

pxb8
pxUnsig32FromString8(pxu32* self, PxFormatOptions options, PxString8 string);

pxb8
pxUnsig64FromString8(pxu64* self, PxFormatOptions options, PxString8 string);

pxb8
pxUnsigFromString8(pxunsig* self, PxFormatOptions options, PxString8 string);

pxb8
pxInt8FromString8(pxi8* self, PxFormatOptions options, PxString8 string);

pxb8
pxInt16FromString8(pxi16* self, PxFormatOptions options, PxString8 string);

pxb8
pxInt32FromString8(pxi32* self, PxFormatOptions options, PxString8 string);

pxb8
pxInt64FromString8(pxi64* self, PxFormatOptions options, PxString8 string);

pxb8
pxIntFromString8(pxint* self, PxFormatOptions options, PxString8 string);

#endif // PX_FORMAT_STRING8_H
