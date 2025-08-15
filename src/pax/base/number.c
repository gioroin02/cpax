#ifndef PX_BASE_NUMBER_C
#define PX_BASE_NUMBER_C

#include "number.h"

pxnat
pxMagnitudeInt(pxint value)
{
    if (value < 0)
        return -px_as(pxnat, value);

    return px_as(pxnat, value);
}

pxn64
pxMagnitudeInt64(pxi32 value)
{
    if (value < 0)
        return -px_as(pxn64, value);

    return px_as(pxn64, value);
}

pxn32
pxMagnitudeInt32(pxi32 value)
{
    if (value < 0)
        return -px_as(pxn32, value);

    return px_as(pxn32, value);
}

pxn16
pxMagnitudeInt16(pxi16 value)
{
    if (value < 0)
        return -px_as(pxn16, value);

    return px_as(pxn16, value);
}

pxn8
pxMagnitudeInt8(pxi8 value)
{
    if (value < 0)
        return -px_as(pxn8, value);

    return px_as(pxn8, value);
}

pxfloat
pxMagnitudeFloat(pxfloat value)
{
    pxnat* bits =
        px_as(pxnat*, &value);

    *bits &= ~PX_FLOAT_SIGN_MASK;

    return value;
}

pxf64
pxMagnitudeFloat64(pxf64 value)
{
    pxn64* bits =
        px_as(pxn64*, &value);

    *bits &= ~PX_F64_SIGN_MASK;

    return value;
}

pxf32
pxMagnitudeFloat32(pxf32 value)
{
    pxn32* bits =
        px_as(pxn32*, &value);

    *bits &= ~PX_F32_SIGN_MASK;

    return value;
}

pxb8
pxDirectionInt(pxint value)
{
    return value < 0 ? 1 : 0;
}

pxb8
pxDirectionInt64(pxi32 value)
{
    return value < 0 ? 1 : 0;
}

pxb8
pxDirectionInt32(pxi32 value)
{
    return value < 0 ? 1 : 0;
}

pxb8
pxDirectionInt16(pxi16 value)
{
    return value < 0 ? 1 : 0;
}

pxb8
pxDirectionInt8(pxi8 value)
{
    return value < 0 ? 1 : 0;
}

pxb8
pxDirectionFloat(pxfloat value)
{
    return value < 0 ? 1 : 0;
}

pxb8
pxDirectionFloat64(pxf64 value)
{
    return value < 0 ? 1 : 0;
}

pxb8
pxDirectionFloat32(pxf32 value)
{
    return value < 0 ? 1 : 0;
}

#endif // PX_BASE_NUMBER_C
