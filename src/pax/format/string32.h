#ifndef PX_FORMAT_STRING32_H
#define PX_FORMAT_STRING32_H

#include "options.h"

pxbool8
pxWord8FromString32(pxword8* self, PxFormatOptions options, PxString32 string);

pxbool8
pxWord16FromString32(pxword16* self, PxFormatOptions options, PxString32 string);

pxbool8
pxWord32FromString32(pxword32* self, PxFormatOptions options, PxString32 string);

pxbool8
pxWord64FromString32(pxword64* self, PxFormatOptions options, PxString32 string);

pxbool8
pxWordFromString32(pxword* self, PxFormatOptions options, PxString32 string);

pxbool8
pxInt8FromString32(pxint8* self, PxFormatOptions options, PxString32 string);

pxbool8
pxInt16FromString32(pxint16* self, PxFormatOptions options, PxString32 string);

pxbool8
pxInt32FromString32(pxint32* self, PxFormatOptions options, PxString32 string);

pxbool8
pxInt64FromString32(pxint64* self, PxFormatOptions options, PxString32 string);

pxbool8
pxIntFromString32(pxint* self, PxFormatOptions options, PxString32 string);

#endif // PX_FORMAT_STRING32_H
