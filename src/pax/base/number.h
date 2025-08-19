#ifndef PX_BASE_NUMBER_H
#define PX_BASE_NUMBER_H

#include "platform.h"
#include "define.h"

typedef char          pxi8;
typedef unsigned char pxu8;
typedef unsigned char pxb8;

#define PX_I8_SIZE pxSize(pxi8)
#define PX_I8_MAX  pxCast(pxi8, 0x7f)
#define PX_I8_MIN  pxCast(pxi8, 0x80)

#define PX_U8_SIZE pxSize(pxu8)
#define PX_U8_MAX  pxCast(pxu8, 0xff)
#define PX_U8_MIN  pxCast(pxu8, 0x00)

typedef short          pxi16;
typedef unsigned short pxu16;
typedef unsigned short pxb16;

#define PX_I16_SIZE pxSize(pxi16)
#define PX_I16_MAX  pxCast(pxi16, 0x7fff)
#define PX_I16_MIN  pxCast(pxi16, 0x8000)

#define PX_U16_SIZE pxSize(pxu16)
#define PX_U16_MAX  pxCast(pxu16, 0xffff)
#define PX_U16_MIN  pxCast(pxu16, 0x0000)

#if PX_WORD >= PX_WORD_32

    typedef long          pxi32;
    typedef unsigned long pxu32;
    typedef unsigned long pxb32;
    typedef float         pxf32;

    #define PX_I32_SIZE pxSize(pxi32)
    #define PX_I32_MAX  pxCast(pxi32, 0x7fffffff)
    #define PX_I32_MIN  pxCast(pxi32, 0x80000000)

    #define PX_U32_SIZE pxSize(pxu32)
    #define PX_U32_MAX  pxCast(pxu32, 0xffffffff)
    #define PX_U32_MIN  pxCast(pxu32, 0x00000000)

    #define PX_F32_SIZE pxSize(pxf32)

    #define PX_F32_EXP_MAX  pxCast(pxi16, 127)
    #define PX_F32_EXP_MIN  pxCast(pxi16, -126)
    #define PX_F32_EXP_BIAS pxCast(pxi16, 127)
    #define PX_F32_EXP_SIZE pxCast(pxi32, 8)
    #define PX_F32_EXP_MASK pxCast(pxu32, 0x7f800000)

    #define PX_F32_FRAC_SIZE pxCast(pxi32, 23)
    #define PX_F32_FRAC_MASK pxCast(pxu32, 0x007fffff)

    #define PX_F32_SIGN_SIZE pxCast(pxi32, 1)
    #define PX_F32_SIGN_MASK pxCast(pxu32, 0x80000000)

#endif

#if PX_WORD >= PX_WORD_64

    typedef long long          pxi64;
    typedef unsigned long long pxu64;
    typedef unsigned long long pxb64;
    typedef double             pxf64;

    #define PX_I64_SIZE pxSize(pxi64)
    #define PX_I64_MAX  pxCast(pxi64, 0x7fffffffffffffff)
    #define PX_I64_MIN  pxCast(pxi64, 0x8000000000000000)

    #define PX_U64_SIZE pxSize(pxu64)
    #define PX_U64_MAX  pxCast(pxu64, 0xffffffffffffffff)
    #define PX_U64_MIN  pxCast(pxu64, 0x0000000000000000)

    #define PX_F64_SIZE pxSize(pxf64)

    #define PX_F64_EXP_MAX  pxCast(pxi32, 1023)
    #define PX_F64_EXP_MIN  pxCast(pxi32, -1022)
    #define PX_F64_EXP_BIAS pxCast(pxi32, 1023)
    #define PX_F64_EXP_SIZE pxCast(pxi64, 11)
    #define PX_F64_EXP_MASK pxCast(pxu64, 0x7ff0000000000000)

    #define PX_F64_FRAC_SIZE pxCast(pxi64, 52)
    #define PX_F64_FRAC_MASK pxCast(pxu64, 0x000fffffffffffff)

    #define PX_F64_SIGN_SIZE pxCast(pxi64, 1)
    #define PX_F64_SIGN_MASK pxCast(pxu64, 0x8000000000000000)

#endif

#if PX_WORD == PX_WORD_64

    typedef pxi64 pxint;
    typedef pxu64 pxunsig;
    typedef pxb64 pxbool;
    typedef pxf64 pxfloat;

    #define PX_INT_SIZE PX_I64_SIZE
    #define PX_INT_MAX  PX_I64_MAX
    #define PX_INT_MIN  PX_I64_MIN

    #define PX_UNSIG_SIZE PX_U64_SIZE
    #define PX_UNSIG_MAX  PX_U64_MAX
    #define PX_UNSIG_MIN  PX_U64_MIN

    #define PX_FLOAT_SIZE PX_F64_SIZE

    #define PX_FLOAT_EXP_MAX   PX_F64_EXP_MAX
    #define PX_FLOAT_EXP_MIN   PX_F64_EXP_MIN
    #define PX_FLOAT_EXP_BIAS  PX_F64_EXP_BIAS
    #define PX_FLOAT_EXP_SIZE  PX_F64_EXP_SIZE
    #define PX_FLOAT_EXP_MASK  PX_F64_EXP_MASK

    #define PX_FLOAT_FRAC_SIZE PX_F64_FRAC_SIZE
    #define PX_FLOAT_FRAC_MASK PX_F64_FRAC_MASK

    #define PX_FLOAT_SIGN_SIZE PX_F64_SIGN_SIZE
    #define PX_FLOAT_SIGN_MASK PX_F64_SIGN_MASK

#elif PX_WORD == PX_WORD_32

    typedef pxi32 pxint;
    typedef pxu32 pxunsig;
    typedef pxb32 pxbool;
    typedef pxf32 pxfloat;

    #define PX_INT_SIZE PX_I32_SIZE
    #define PX_INT_MAX  PX_I32_MAX
    #define PX_INT_MIN  PX_I32_MIN

    #define PX_UNSIG_SIZE PX_U32_SIZE
    #define PX_UNSIG_MAX  PX_U32_MAX
    #define PX_UNSIG_MIN  PX_U32_MIN

    #define PX_FLOAT_SIZE PX_F32_SIZE

    #define PX_FLOAT_EXP_MAX   PX_F32_EXP_MAX
    #define PX_FLOAT_EXP_MIN   PX_F32_EXP_MIN
    #define PX_FLOAT_EXP_BIAS  PX_F32_EXP_BIAS
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

pxu8
pxMagnitudeInt8(pxi8 value);

pxu16
pxMagnitudeInt16(pxi16 value);

pxu32
pxMagnitudeInt32(pxi32 value);

pxu64
pxMagnitudeInt64(pxi64 value);

pxunsig
pxMagnitudeInt(pxint value);

/* Floating magnitude */

pxf32
pxMagnitudeFloat32(pxf32 value);

pxf64
pxMagnitudeFloat64(pxf64 value);

pxfloat
pxMagnitudeFloat(pxfloat value);

/* Integer direction */

pxi8
pxDirectionInt8(pxi8 value);

pxi8
pxDirectionInt16(pxi16 value);

pxi8
pxDirectionInt32(pxi32 value);

pxi8
pxDirectionInt64(pxi64 value);

pxi8
pxDirectionInt(pxint value);

/* Floating sign */

pxi8
pxDirectionFloat32(pxf32 value);

pxi8
pxDirectionFloat64(pxf64 value);

pxi8
pxDirectionFloat(pxfloat value);

#endif // PX_BASE_NUMBER_H
