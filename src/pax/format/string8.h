#ifndef PX_FORMAT_STRING8_H
#define PX_FORMAT_STRING8_H

#include "options.h"

pxbool8
pxWord8FromString8(pxword8* self, PxFormatOptions options, PxString8 string);

pxbool8
pxWord16FromString8(pxword16* self, PxFormatOptions options, PxString8 string);

pxbool8
pxWord32FromString8(pxword32* self, PxFormatOptions options, PxString8 string);

pxbool8
pxWord64FromString8(pxword64* self, PxFormatOptions options, PxString8 string);

pxbool8
pxWordFromString8(pxword* self, PxFormatOptions options, PxString8 string);

#endif // PX_FORMAT_STRING8_H
