#ifndef PX_FORMAT_STRING16_H
#define PX_FORMAT_STRING16_H

#include "options.h"

pxbool8
pxWord8FromString16(pxword8* self, PxFormatOptions options, PxString16 string);

pxbool8
pxWord16FromString16(pxword16* self, PxFormatOptions options, PxString16 string);

pxbool8
pxWord32FromString16(pxword32* self, PxFormatOptions options, PxString16 string);

pxbool8
pxWord64FromString16(pxword64* self, PxFormatOptions options, PxString16 string);

pxbool8
pxWordFromString16(pxword* self, PxFormatOptions options, PxString16 string);

pxbool8
pxInt8FromString16(pxint8* self, PxFormatOptions options, PxString16 string);

pxbool8
pxInt16FromString16(pxint16* self, PxFormatOptions options, PxString16 string);

pxbool8
pxInt32FromString16(pxint32* self, PxFormatOptions options, PxString16 string);

pxbool8
pxInt64FromString16(pxint64* self, PxFormatOptions options, PxString16 string);

pxbool8
pxIntFromString16(pxint* self, PxFormatOptions options, PxString16 string);

#endif // PX_FORMAT_STRING16_H
