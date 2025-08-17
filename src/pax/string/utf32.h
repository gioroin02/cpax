#ifndef PX_STRING_UTF32_H
#define PX_STRING_UTF32_H

#include "unicode.h"

#define PX_UTF32_MIN_UNITS pxCast(pxint, 1)
#define PX_UTF32_MAX_UNITS pxCast(pxint, 1)

typedef struct PxUtf32
{
    union
    {
        struct {
            pxword32 a;
        };

        pxword32 memory[PX_UTF32_MAX_UNITS];
    };

    pxint size;
}
PxUtf32;

pxbool16
pxUtf32Encode(PxUtf32* self, pxint32 value);

pxint
pxUtf32WriteMemoryForw(pxword32* memory, pxint length, pxint index, pxint32 value);

pxint
pxUtf32WriteMemoryBack(pxword32* memory, pxint length, pxint index, pxint32 value);

pxbool16
pxUtf32Decode(PxUtf32* self, pxint32* value);

pxint
pxUtf32ReadMemoryForw(pxword32* memory, pxint length, pxint index, pxint32* value);

pxint
pxUtf32ReadMemoryBack(pxword32* memory, pxint length, pxint index, pxint32* value);

pxint
pxUtf32UnitsToWrite(pxint32 value);

pxint
pxUtf32UnitsToRead(pxword32 value);

#endif // PX_STRING_UTF32_H
