#ifndef PX_BASE_NUMBER_C
#define PX_BASE_NUMBER_C

#include "number.h"

pxword
pxMagnitudeInt(pxint value)
{
    if (value < 0)
        return -pxCast(pxword, value);

    return pxCast(pxword, value);
}

pxword64
pxMagnitudeInt64(pxint64 value)
{
    if (value < 0)
        return -pxCast(pxword64, value);

    return pxCast(pxword64, value);
}

pxword32
pxMagnitudeInt32(pxint32 value)
{
    if (value < 0)
        return -pxCast(pxword32, value);

    return pxCast(pxword32, value);
}

pxword16
pxMagnitudeInt16(pxint16 value)
{
    if (value < 0)
        return -pxCast(pxword16, value);

    return pxCast(pxword16, value);
}

pxword8
pxMagnitudeInt8(pxint8 value)
{
    if (value < 0)
        return -pxCast(pxword8, value);

    return pxCast(pxword8, value);
}

pxfloat
pxMagnitudeFloat(pxfloat value)
{
    pxword* bits =
        pxCast(pxword*, &value);

    *bits &= ~PX_FLOAT_SIGN_MASK;

    return value;
}

pxfloat64
pxMagnitudeFloat64(pxfloat64 value)
{
    pxword64* bits =
        pxCast(pxword64*, &value);

    *bits &= ~PX_FLOAT64_SIGN_MASK;

    return value;
}

pxfloat32
pxMagnitudeFloat32(pxfloat32 value)
{
    pxword32* bits =
        pxCast(pxword32*, &value);

    *bits &= ~PX_FLOAT32_SIGN_MASK;

    return value;
}

pxbool8
pxDirectionInt(pxint value)
{
    return value < 0 ? 1 : 0;
}

pxbool8
pxDirectionInt64(pxint64 value)
{
    return value < 0 ? 1 : 0;
}

pxbool8
pxDirectionInt32(pxint32 value)
{
    return value < 0 ? 1 : 0;
}

pxbool8
pxDirectionInt16(pxint16 value)
{
    return value < 0 ? 1 : 0;
}

pxbool8
pxDirectionInt8(pxint8 value)
{
    return value < 0 ? 1 : 0;
}

pxbool8
pxDirectionFloat(pxfloat value)
{
    return value < 0 ? 1 : 0;
}

pxbool8
pxDirectionFloat64(pxfloat64 value)
{
    return value < 0 ? 1 : 0;
}

pxbool8
pxDirectionFloat32(pxfloat32 value)
{
    return value < 0 ? 1 : 0;
}

#endif // PX_BASE_NUMBER_C
