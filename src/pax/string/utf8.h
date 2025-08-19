#ifndef PX_STRING_UTF8_H
#define PX_STRING_UTF8_H

#include "unicode.h"

#define PX_UTF8_MIN_UNITS pxCast(pxint, 1)
#define PX_UTF8_MAX_UNITS pxCast(pxint, 4)

typedef struct PxUtf8
{
    union
    {
        struct {
            pxu8 a, b, c, d;
        };

        pxu8 memory[PX_UTF8_MAX_UNITS];
    };

    pxint size;
}
PxUtf8;

pxb8
pxUtf8Encode(PxUtf8* self, pxi32 value);

pxint
pxUtf8WriteMemoryForw(pxu8* memory, pxint length, pxint index, pxi32 value);

pxint
pxUtf8WriteMemoryBack(pxu8* memory, pxint length, pxint index, pxi32 value);

pxb8
pxUtf8Decode(PxUtf8* self, pxi32* value);

pxint
pxUtf8ReadMemoryForw(pxu8* memory, pxint length, pxint index, pxi32* value);

pxint
pxUtf8ReadMemoryBack(pxu8* memory, pxint length, pxint index, pxi32* value);

pxint
pxUtf8UnitsToWrite(pxi32 value);

pxint
pxUtf8UnitsToRead(pxu8 value);

pxb8
pxUtf8IsTrailing(pxu8 value);

pxb8
pxUtf8IsOverlong(pxi32 value, pxint units);

#endif // PX_STRING_UTF8_H
