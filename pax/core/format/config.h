#ifndef PX_CORE_FORMAT_CONFIG_H
#define PX_CORE_FORMAT_CONFIG_H

#include "import.h"

typedef enum PxFormatRadix
{
    PX_FORMAT_RADIX_NONE = 0,
    PX_FORMAT_RADIX_2    = 2,
    PX_FORMAT_RADIX_8    = 8,
    PX_FORMAT_RADIX_10   = 10,
    PX_FORMAT_RADIX_16   = 16,
}
PxFormatRadix;

typedef enum PxFormatFlag
{
    PX_FORMAT_FLAG_NONE  = 0x0,
    PX_FORMAT_FLAG_PLUS  = 0x1,
    PX_FORMAT_FLAG_UPPER = 0x2,
}
PxFormatFlag;

pxuword
pxMagnitudeFormatRadix(PxFormatRadix radix);

pxi32
pxUnicodeFromDigit(pxuword value, PxFormatRadix radix, PxFormatFlag flags);

pxuword
pxDigitFromUnicode(pxi32 value, PxFormatRadix radix, PxFormatFlag flags);

#endif // PX_CORE_FORMAT_CONFIG_H
