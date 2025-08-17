#ifndef PX_STRING_UTF8_H
#define PX_STRING_UTF8_H

#include "unicode.h"

#define PX_UTF8_MIN_UNITS pxCast(pxint, 1)
#define PX_UTF8_MAX_UNITS pxCast(pxint, 4)

typedef struct
{
    union
    {
        struct {
            pxword8 a, b, c, d;
        };

        pxword8 memory[PX_UTF8_MAX_UNITS];
    };

    pxint size;
}
PxUtf8;

pxbool8
pxUtf8Encode(PxUtf8* self, pxint32 value);

pxint
pxUtf8WriteMemoryForw(pxword8* memory, pxint length, pxint index, pxint32 value);

pxint
pxUtf8WriteMemoryBack(pxword8* memory, pxint length, pxint index, pxint32 value);

pxbool8
pxUtf8Decode(PxUtf8* self, pxint32* value);

pxint
pxUtf8ReadMemoryForw(pxword8* memory, pxint length, pxint index, pxint32* value);

pxint
pxUtf8ReadMemoryBack(pxword8* memory, pxint length, pxint index, pxint32* value);

pxint
pxUtf8UnitsToWrite(pxint32 value);

pxint
pxUtf8UnitsToRead(pxword8 value);

pxbool8
pxUtf8IsTrailing(pxword8 value);

pxbool8
pxUtf8IsOverlong(pxint32 value, pxint units);

#endif // PX_STRING_UTF8_H
