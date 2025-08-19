#ifndef PX_BASE_NUMBER_C
#define PX_BASE_NUMBER_C

#include "number.h"

pxu8
pxMagnitudeInt8(pxi8 value)
{
    if (value < 0)
        return -pxCast(pxu8, value);

    return pxCast(pxu8, value);
}

pxu16
pxMagnitudeInt16(pxi16 value)
{
    if (value < 0)
        return -pxCast(pxu16, value);

    return pxCast(pxu16, value);
}

pxu32
pxMagnitudeInt32(pxi32 value)
{
    if (value < 0)
        return -pxCast(pxu32, value);

    return pxCast(pxu32, value);
}

pxu64
pxMagnitudeInt64(pxi64 value)
{
    if (value < 0)
        return -pxCast(pxu64, value);

    return pxCast(pxu64, value);
}

pxunsig
pxMagnitudeInt(pxint value)
{
    if (value < 0)
        return -pxCast(pxunsig, value);

    return pxCast(pxunsig, value);
}

pxf32
pxMagnitudeFloat32(pxf32 value)
{
    pxu32* bits =
        pxCast(pxu32*, &value);

    *bits &= ~PX_F32_SIGN_MASK;

    return value;
}

pxf64
pxMagnitudeFloat64(pxf64 value)
{
    pxu64* bits =
        pxCast(pxu64*, &value);

    *bits &= ~PX_F64_SIGN_MASK;

    return value;
}

pxfloat
pxMagnitudeFloat(pxfloat value)
{
    pxunsig* bits =
        pxCast(pxunsig*, &value);

    *bits &= ~PX_FLOAT_SIGN_MASK;

    return value;
}

pxi8
pxDirectionInt8(pxi8 value)
{
    if (value > 0) return +1;
    if (value < 0) return -1;

    return 0;
}

pxi8
pxDirectionInt16(pxi16 value)
{
    if (value > 0) return +1;
    if (value < 0) return -1;

    return 0;
}

pxi8
pxDirectionInt32(pxi32 value)
{
    if (value > 0) return +1;
    if (value < 0) return -1;

    return 0;
}

pxi8
pxDirectionInt64(pxi64 value)
{
    if (value > 0) return +1;
    if (value < 0) return -1;

    return 0;
}

pxi8
pxDirectionInt(pxint value)
{
    if (value > 0) return +1;
    if (value < 0) return -1;

    return 0;
}

pxi8
pxDirectionFloat32(pxf32 value)
{
    if (value > 0) return +1;
    if (value < 0) return -1;

    return 0;
}

pxi8
pxDirectionFloat64(pxf64 value)
{
    if (value > 0) return +1;
    if (value < 0) return -1;

    return 0;
}

pxi8
pxDirectionFloat(pxfloat value)
{
    if (value > 0) return +1;
    if (value < 0) return -1;

    return 0;
}

#endif // PX_BASE_NUMBER_C
