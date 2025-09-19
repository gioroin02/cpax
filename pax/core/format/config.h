#ifndef PX_CORE_FORMAT_CONFIG_H
#define PX_CORE_FORMAT_CONFIG_H

#include "import.h"

typedef enum PxFmtRadix
{
    PX_FORMAT_RADIX_NONE = 0,
    PX_FORMAT_RADIX_2    = 2,
    PX_FORMAT_RADIX_8    = 8,
    PX_FORMAT_RADIX_10   = 10,
    PX_FORMAT_RADIX_16   = 16,
}
PxFmtRadix;

typedef enum PxFmtFlag
{
    PX_FORMAT_FLAG_NONE  = 0x0,
    PX_FORMAT_FLAG_PLUS  = 0x1,
    PX_FORMAT_FLAG_UPPER = 0x2,
}
PxFmtFlag;

pxuword
pxMagnitudeFmtRadix(PxFmtRadix radix);

pxi32
pxUnicodeFromDigit(pxuword value, PxFmtRadix radix, PxFmtFlag flags);

pxuword
pxDigitFromUnicode(pxi32 value, PxFmtRadix radix, PxFmtFlag flags);

#endif // PX_CORE_FORMAT_CONFIG_H
