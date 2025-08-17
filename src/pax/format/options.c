#ifndef PX_FORMAT_OPTIONS_C
#define PX_FORMAT_OPTIONS_C

#include "options.h"

PxFormatOptions
pxFormatOptionsRadix(pxword8 radix)
{
    return (PxFormatOptions) {
        .radix = radix
    };
}

PxFormatOptions
pxFormatOptions(pxword8 radix, PxFormatFlag flags)
{
    if (flags < 0)
        return (PxFormatOptions) {0};

    return (PxFormatOptions) {
        .flags = flags,
        .radix = radix,
    };
}

#endif // PX_FORMAT_OPTIONS_C
