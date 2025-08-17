#ifndef PX_STRING_UTF16_H
#define PX_STRING_UTF16_H

#include "unicode.h"

#define PX_UTF16_MIN_UNITS pxCast(pxint, 1)
#define PX_UTF16_MAX_UNITS pxCast(pxint, 2)

typedef struct PxUtf16
{
    union
    {
        struct {
            pxword16 a, b;
        };

        pxword16 memory[PX_UTF16_MAX_UNITS];
    };

    pxint size;
}
PxUtf16;

pxbool8
pxUtf16Encode(PxUtf16* self, pxint32 value);

pxint
pxUtf16WriteMemoryForw(pxword16* memory, pxint length, pxint index, pxint32 value);

pxint
pxUtf16WriteMemoryBack(pxword16* memory, pxint length, pxint index, pxint32 value);

pxbool8
pxUtf16Decode(PxUtf16* self, pxint32* value);

pxint
pxUtf16ReadMemoryForw(pxword16* memory, pxint length, pxint index, pxint32* value);

pxint
pxUtf16ReadMemoryBack(pxword16* memory, pxint length, pxint index, pxint32* value);

pxint
pxUtf16UnitsToWrite(pxint32 value);

pxint
pxUtf16UnitsToRead(pxword16 value);

#endif // PX_STRING_UTF16_H
