#ifndef PAX_BASE_NUMBER_C
#define PAX_BASE_NUMBER_C

#include "number.h"

Nat
pax_abs_int(Int value)
{
    if (value < 0)
        return -pax_as(Nat, value);

    return pax_as(Nat, value);
}

nat64
pax_abs_int64(int64 value)
{
    if (value < 0)
        return -pax_as(nat64, value);

    return pax_as(nat64, value);
}

nat32
pax_abs_int32(int32 value)
{
    if (value < 0)
        return -pax_as(nat32, value);

    return pax_as(nat32, value);
}

nat16
pax_abs_int16(int16 value)
{
    if (value < 0)
        return -pax_as(nat16, value);

    return pax_as(nat16, value);
}

nat8
pax_abs_int8(int8 value)
{
    if (value < 0)
        return -pax_as(nat8, value);

    return pax_as(nat8, value);
}

Float
pax_abs_float(Float value)
{
    Nat* bits =
        pax_as(Nat*, &value);

    *bits &= ~PAX_FLOAT_SIGN_MASK;

    return value;
}

float64
pax_abs_float64(float64 value)
{
    nat64* bits =
        pax_as(nat64*, &value);

    *bits &= ~PAX_FLOAT64_SIGN_MASK;

    return value;
}

float32
pax_abs_float32(float32 value)
{
    nat32* bits =
        pax_as(nat32*, &value);

    *bits &= ~PAX_FLOAT32_SIGN_MASK;

    return value;
}

bool8
pax_sig_int(Int value)
{
    return value < 0 ? 1 : 0;
}

bool8
pax_sig_int64(int64 value)
{
    return value < 0 ? 1 : 0;
}

bool8
pax_sig_int32(int32 value)
{
    return value < 0 ? 1 : 0;
}

bool8
pax_sig_int16(int16 value)
{
    return value < 0 ? 1 : 0;
}

bool8
pax_sig_int8(int8 value)
{
    return value < 0 ? 1 : 0;
}

bool8
pax_sig_float(Float value)
{
    return value < 0 ? 1 : 0;
}

bool8
pax_sig_float64(float64 value)
{
    return value < 0 ? 1 : 0;
}

bool8
pax_sig_float32(float32 value)
{
    return value < 0 ? 1 : 0;
}

#endif // PAX_BASE_NUMBER_C
