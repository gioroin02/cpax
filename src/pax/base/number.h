#ifndef PX_BASE_NUMBER_H
#define PX_BASE_NUMBER_H

#include "platform.h"
#include "define.h"

typedef char          pxint8;
typedef unsigned char pxword8;
typedef unsigned char pxbool8;

#define PX_INT8_MAX pxCast(pxint8, 0x7f)
#define PX_INT8_MIN pxCast(pxint8, 0x80)

#define PX_WORD8_MAX pxCast(pxword8, 0xff)
#define PX_WORD8_MIN pxCast(pxword8, 0x00)

typedef short          pxint16;
typedef unsigned short pxword16;
typedef unsigned short pxbool16;

#define PX_INT16_MAX pxCast(pxint16, 0x7fff)
#define PX_INT16_MIN pxCast(pxint16, 0x8000)

#define PX_WORD16_MAX pxCast(pxword16, 0xffff)
#define PX_WORD16_MIN pxCast(pxword16, 0x0000)

#if PX_SIZE >= PX_SIZE_32

    typedef long          pxint32;
    typedef unsigned long pxword32;
    typedef unsigned long pxbool32;
    typedef float         pxfloat32;

    #define PX_INT32_MAX pxCast(pxint32, 0x7fffffff)
    #define PX_INT32_MIN pxCast(pxint32, 0x80000000)

    #define PX_WORD32_MAX pxCast(pxword32, 0xffffffff)
    #define PX_WORD32_MIN pxCast(pxword32, 0x00000000)

    #define PX_FLOAT32_EXP_MAX  pxCast(pxint16, 127)
    #define PX_FLOAT32_EXP_MIN  pxCast(pxint16, -126)
    #define PX_FLOAT32_EXP_BIAS pxCast(pxint16, 127)
    #define PX_FLOAT32_EXP_SIZE pxCast(pxint32, 8)
    #define PX_FLOAT32_EXP_MASK pxCast(pxword32, 0x7f800000)

    #define PX_FLOAT32_FRAC_SIZE pxCast(pxint32, 23)
    #define PX_FLOAT32_FRAC_MASK pxCast(pxword32, 0x007fffff)

    #define PX_FLOAT32_SIGN_SIZE pxCast(pxint32, 1)
    #define PX_FLOAT32_SIGN_MASK pxCast(pxword32, 0x80000000)

#endif

#if PX_SIZE >= PX_SIZE_64

    typedef long long          pxint64;
    typedef unsigned long long pxword64;
    typedef unsigned long long pxbool64;
    typedef double             pxfloat64;

    #define PX_INT64_MAX pxCast(pxint64, 0x7fffffffffffffff)
    #define PX_INT64_MIN pxCast(pxint64, 0x8000000000000000)

    #define PX_WORD64_MAX pxCast(pxword64, 0xffffffffffffffff)
    #define PX_WORD64_MIN pxCast(pxword64, 0x0000000000000000)

    #define PX_FLOAT64_EXP_MAX  pxCast(pxint32, 1023)
    #define PX_FLOAT64_EXP_MIN  pxCast(pxint32, -1022)
    #define PX_FLOAT64_EXP_BIAS pxCast(pxint32, 1023)
    #define PX_FLOAT64_EXP_SIZE pxCast(pxint64, 11)
    #define PX_FLOAT64_EXP_MASK pxCast(pxword64, 0x7ff0000000000000)

    #define PX_FLOAT64_FRAC_SIZE pxCast(pxint64, 52)
    #define PX_FLOAT64_FRAC_MASK pxCast(pxword64, 0x000fffffffffffff)

    #define PX_FLOAT64_SIGN_SIZE pxCast(pxint64, 1)
    #define PX_FLOAT64_SIGN_MASK pxCast(pxword64, 0x8000000000000000)

#endif

#if PX_SIZE == PX_SIZE_64

    typedef pxint64   pxint;
    typedef pxword64  pxword;
    typedef pxbool64  pxbool;
    typedef pxfloat64 pxfloat;

    #define PX_INT_MAX PX_INT64_MAX
    #define PX_INT_MIN PX_INT64_MIN

    #define PX_WORD_MAX PX_WORD64_MAX
    #define PX_WORD_MIN PX_WORD64_MIN

    #define PX_FLOAT_EXP_MAX   PX_FLOAT64_EXP_MAX
    #define PX_FLOAT_EXP_MIN   PX_FLOAT64_EXP_MIN
    #define PX_FLOAT_EXP_BIAS  PX_FLOAT64_EXP_BIAS
    #define PX_FLOAT_EXP_SIZE  PX_FLOAT64_EXP_SIZE
    #define PX_FLOAT_EXP_MASK  PX_FLOAT64_EXP_MASK

    #define PX_FLOAT_FRAC_SIZE PX_FLOAT64_FRAC_SIZE
    #define PX_FLOAT_FRAC_MASK PX_FLOAT64_FRAC_MASK

    #define PX_FLOAT_SIGN_SIZE PX_FLOAT64_SIGN_SIZE
    #define PX_FLOAT_SIGN_MASK PX_FLOAT64_SIGN_MASK

#elif PX_SIZE == PX_SIZE_32

    typedef pxint32   pxint;
    typedef pxword32  pxword;
    typedef pxbool32  pxbool;
    typedef pxfloat32 pxfloat;

    #define PX_INT_MAX PX_INT32_MAX
    #define PX_INT_MIN PX_INT32_MIN

    #define PX_WORD_MAX PX_WORD32_MAX
    #define PX_WORD_MIN PX_WORD32_MIN

    #define PX_FLOAT_EXP_MAX   PX_FLOAT32_EXP_MAX
    #define PX_FLOAT_EXP_MIN   PX_FLOAT32_EXP_MIN
    #define PX_FLOAT_EXP_BIAS  PX_FLOAT32_EXP_BIAS
    #define PX_FLOAT_EXP_SIZE  PX_FLOAT32_EXP_SIZE
    #define PX_FLOAT_EXP_MASK  PX_FLOAT32_EXP_MASK

    #define PX_FLOAT_FRAC_SIZE PX_FLOAT32_FRAC_SIZE
    #define PX_FLOAT_FRAC_MASK PX_FLOAT32_FRAC_MASK

    #define PX_FLOAT_SIGN_SIZE PX_FLOAT32_SIGN_SIZE
    #define PX_FLOAT_SIGN_MASK PX_FLOAT32_SIGN_MASK

#else

    #error "Unknown platform"

#endif

/* Integer magnitude */

pxword8
pxMagnitudeInt8(pxint8 value);

pxword16
pxMagnitudeInt16(pxint16 value);

pxword32
pxMagnitudeInt32(pxint32 value);

pxword64
pxMagnitudeInt64(pxint64 value);

pxword
pxMagnitudeInt(pxint value);

/* Floating magnitude */

pxfloat32
pxMagnitudeFloat32(pxfloat32 value);

pxfloat64
pxMagnitudeFloat64(pxfloat64 value);

pxfloat
pxMagnitudeFloat(pxfloat value);

/* Integer direction */

pxbool8
pxDirectionInt8(pxint8 value);

pxbool8
pxDirectionInt16(pxint16 value);

pxbool8
pxDirectionInt32(pxint32 value);

pxbool8
pxDirectionInt64(pxint64 value);

pxbool8
pxDirectionInt(pxint value);

/* Floating sign */

pxbool8
pxDirectionFloat32(pxfloat32 value);

pxbool8
pxDirectionFloat64(pxfloat64 value);

pxbool8
pxDirectionFloat(pxfloat value);

#endif // PX_BASE_NUMBER_H
