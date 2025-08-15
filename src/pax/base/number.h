#ifndef PX_BASE_NUMBER_H
#define PX_BASE_NUMBER_H

#include "platform.h"
#include "define.h"

typedef char          pxi8;
typedef unsigned char pxn8;
typedef unsigned char pxb8;

#define PX_I8_MAX px_as(pxi8, 0x7f)
#define PX_I8_MIN px_as(pxi8, 0x80)

#define PX_N8_MAX px_as(pxn8, 0xff)
#define PX_N8_MIN px_as(pxn8, 0x00)

typedef short          pxi16;
typedef unsigned short pxn16;
typedef unsigned short pxb16;

#define PX_I16_MAX px_as(pxi16, 0x7fff)
#define PX_I16_MIN px_as(pxi16, 0x8000)

#define PX_N16_MAX px_as(pxn16, 0xffff)
#define PX_N16_MIN px_as(pxn16, 0x0000)

#if PX_SIZE >= PX_SIZE_32

    typedef long          pxi32;
    typedef unsigned long pxn32;
    typedef unsigned long pxb32;
    typedef float         pxf32;

    #define PX_I32_MAX px_as(pxi32, 0x7fffffff)
    #define PX_I32_MIN px_as(pxi32, 0x80000000)

    #define PX_N32_MAX px_as(pxn32, 0xffffffff)
    #define PX_N32_MIN px_as(pxn32, 0x00000000)

    #define PX_F32_EXP_MAX  px_as(pxi16, 127)
    #define PX_F32_EXP_BIAS px_as(pxi16, 127)
    #define PX_F32_EXP_MIN  px_as(pxi16, -126)
    #define PX_F32_EXP_SIZE px_as(pxi32, 8)
    #define PX_F32_EXP_MASK px_as(pxn32, 0x7f800000)

    #define PX_F32_FRAC_SIZE px_as(pxi32, 23)
    #define PX_F32_FRAC_MASK px_as(pxn32, 0x007fffff)

    #define PX_F32_SIGN_SIZE px_as(pxi32, 1)
    #define PX_F32_SIGN_MASK px_as(pxn32, 0x80000000)

#endif

#if PX_SIZE >= PX_SIZE_64

    typedef long long          pxi64;
    typedef unsigned long long pxn64;
    typedef unsigned long long pxb64;
    typedef double             pxf64;

    #define PX_I64_MAX px_as(pxi64, 0x7fffffffffffffff)
    #define PX_I64_MIN px_as(pxi64, 0x8000000000000000)

    #define PX_N64_MAX px_as(pxn64, 0xffffffffffffffff)
    #define PX_N64_MIN px_as(pxn64, 0x0000000000000000)

    #define PX_F64_EXP_BIAS px_as(pxi32, 1023)
    #define PX_F64_EXP_MAX  px_as(pxi32, 1023)
    #define PX_F64_EXP_MIN  px_as(pxi32, -1022)
    #define PX_F64_EXP_SIZE px_as(pxi64, 11)
    #define PX_F64_EXP_MASK px_as(pxn64, 0x7ff0000000000000)

    #define PX_F64_FRAC_SIZE px_as(pxi64, 52)
    #define PX_F64_FRAC_MASK px_as(pxn64, 0x000fffffffffffff)

    #define PX_F64_SIGN_SIZE px_as(pxi64, 1)
    #define PX_F64_SIGN_MASK px_as(pxn64, 0x8000000000000000)

#endif

#if PX_SIZE == PX_SIZE_64

    typedef pxi64 pxint;
    typedef pxn64 pxnat;
    typedef pxb64 pxbool;
    typedef pxf64 pxfloat;

    #define PX_INT_MAX PX_I64_MAX
    #define PX_INT_MIN PX_I64_MIN

    #define PX_NAT_MAX PX_N64_MAX
    #define PX_NAT_MIN PX_N64_MIN

    #define PX_FLOAT_EXP_BIAS  PX_F64_EXP_BIAS
    #define PX_FLOAT_EXP_MAX   PX_F64_EXP_MAX
    #define PX_FLOAT_EXP_MIN   PX_F64_EXP_MIN
    #define PX_FLOAT_EXP_SIZE  PX_F64_EXP_SIZE
    #define PX_FLOAT_EXP_MASK  PX_F64_EXP_MASK

    #define PX_FLOAT_FRAC_SIZE PX_F64_FRAC_SIZE
    #define PX_FLOAT_FRAC_MASK PX_F64_FRAC_MASK

    #define PX_FLOAT_SIGN_SIZE PX_F64_SIGN_SIZE
    #define PX_FLOAT_SIGN_MASK PX_F64_SIGN_MASK

#elif PX_SIZE == PX_SIZE_32

    typedef pxi32 pxint;
    typedef pxn32 pxnat;
    typedef pxb32 pxbool;
    typedef pxf32 pxfloat;

    #define PX_INT_MAX PX_I32_MAX
    #define PX_INT_MIN PX_I32_MIN

    #define PX_NAT_MAX PX_N32_MAX
    #define PX_NAT_MIN PX_N32_MIN

    #define PX_FLOAT_EXP_BIAS  PX_F32_EXP_BIAS
    #define PX_FLOAT_EXP_MAX   PX_F32_EXP_MAX
    #define PX_FLOAT_EXP_MIN   PX_F32_EXP_MIN
    #define PX_FLOAT_EXP_SIZE  PX_F32_EXP_SIZE
    #define PX_FLOAT_EXP_MASK  PX_F32_EXP_MASK

    #define PX_FLOAT_FRAC_SIZE PX_F32_FRAC_SIZE
    #define PX_FLOAT_FRAC_MASK PX_F32_FRAC_MASK

    #define PX_FLOAT_SIGN_SIZE PX_F32_SIGN_SIZE
    #define PX_FLOAT_SIGN_MASK PX_F32_SIGN_MASK

#else

    #error "Unknown platform"

#endif

/* Integer magnitude */

pxnat
pxMagnitudeInt(pxint value);

pxn64
pxMagnitudeInt64(pxi32 value);

pxn32
pxMagnitudeInt32(pxi32 value);

pxn16
pxMagnitudeInt16(pxi16 value);

pxn8
pxMagnitudeInt8(pxi8 value);

/* Floating magnitude */

pxfloat
pxMagnitudeFloat(pxfloat value);

pxf64
pxMagnitudeFloat64(pxf64 value);

pxf32
pxMagnitudeFloat32(pxf32 value);

/* Integer direction */

pxb8
pxDirectionInt(pxint value);

pxb8
pxDirectionInt64(pxi32 value);

pxb8
pxDirectionInt32(pxi32 value);

pxb8
pxDirectionInt16(pxi16 value);

pxb8
pxDirectionInt8(pxi8 value);

/* Floating sign */

pxb8
pxDirectionFloat(pxfloat value);

pxb8
pxDirectionFloat64(pxf64 value);

pxb8
pxDirectionFloat32(pxf32 value);

#endif // PX_BASE_NUMBER_H
