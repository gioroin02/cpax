#ifndef PX_FORMAT_STRING16_H
#define PX_FORMAT_STRING16_H

#include "options.h"

pxb8
pxUnsig8FromString16(pxu8* self, PxFormatOptions options, PxString16 string);

pxb8
pxUnsig16FromString16(pxu16* self, PxFormatOptions options, PxString16 string);

pxb8
pxUnsig32FromString16(pxu32* self, PxFormatOptions options, PxString16 string);

pxb8
pxUnsig64FromString16(pxu64* self, PxFormatOptions options, PxString16 string);

pxb8
pxUnsigFromString16(pxunsig* self, PxFormatOptions options, PxString16 string);

pxb8
pxInt8FromString16(pxi8* self, PxFormatOptions options, PxString16 string);

pxb8
pxInt16FromString16(pxi16* self, PxFormatOptions options, PxString16 string);

pxb8
pxInt32FromString16(pxi32* self, PxFormatOptions options, PxString16 string);

pxb8
pxInt64FromString16(pxi64* self, PxFormatOptions options, PxString16 string);

pxb8
pxIntFromString16(pxint* self, PxFormatOptions options, PxString16 string);

#endif // PX_FORMAT_STRING16_H
