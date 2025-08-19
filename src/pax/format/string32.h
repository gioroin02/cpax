#ifndef PX_FORMAT_STRING32_H
#define PX_FORMAT_STRING32_H

#include "options.h"

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
