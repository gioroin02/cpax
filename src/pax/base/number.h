#ifndef PAX_BASE_NUMBER_H
#define PAX_BASE_NUMBER_H

#include "platform.h"
#include "define.h"

//
// Types
//

typedef char          int8;
typedef unsigned char nat8;
typedef unsigned char bool8;

static const int8 PAX_INT8_MAX = pax_as(int8, 0x7f);
static const int8 PAX_INT8_MIN = pax_as(int8, 0x80);

static const nat8 PAX_NAT8_MAX = pax_as(nat8, 0xff);
static const nat8 PAX_NAT8_MIN = pax_as(nat8, 0x00);

typedef short          int16;
typedef unsigned short nat16;
typedef unsigned short bool16;

static const int16 PAX_INT16_MAX = pax_as(int16, 0x7fff);
static const int16 PAX_INT16_MIN = pax_as(int16, 0x8000);

static const nat16 PAX_NAT16_MAX = pax_as(nat16, 0xffff);
static const nat16 PAX_NAT16_MIN = pax_as(nat16, 0x0000);

#if PAX_SIZE >= PAX_SIZE_32

    typedef long          int32;
    typedef unsigned long nat32;
    typedef unsigned long bool32;
    typedef float         float32;

    static const int32 PAX_INT32_MAX = pax_as(int32, 0x7fffffff);
    static const int32 PAX_INT32_MIN = pax_as(int32, 0x80000000);

    static const nat32 PAX_NAT32_MAX = pax_as(nat32, 0xffffffff);
    static const nat32 PAX_NAT32_MIN = pax_as(nat32, 0x00000000);

    static const int16 PAX_FLOAT32_EXP_MAX  = pax_as(int16, 127);
    static const int16 PAX_FLOAT32_EXP_BIAS = pax_as(int16, 127);
    static const int16 PAX_FLOAT32_EXP_MIN  = pax_as(int16, -126);
    static const int32 PAX_FLOAT32_EXP_SIZE = pax_as(int32, 8);
    static const nat32 PAX_FLOAT32_EXP_MASK = pax_as(nat32, 0x7f800000);

    static const int32 PAX_FLOAT32_FRAC_SIZE = pax_as(int32, 23);
    static const nat32 PAX_FLOAT32_FRAC_MASK = pax_as(nat32, 0x007fffff);

    static const int32 PAX_FLOAT32_SIGN_SIZE = pax_as(int32, 1);
    static const nat32 PAX_FLOAT32_SIGN_MASK = pax_as(nat32, 0x80000000);

#endif

#if PAX_SIZE >= PAX_SIZE_64

    typedef long long          int64;
    typedef unsigned long long nat64;
    typedef unsigned long long bool64;
    typedef double             float64;

    static const int64 PAX_INT64_MAX = pax_as(int64, 0x7fffffff);
    static const int64 PAX_INT64_MIN = pax_as(int64, 0x80000000);

    static const nat64 PAX_NAT64_MAX = pax_as(nat64, 0xffffffff);
    static const nat64 PAX_NAT64_MIN = pax_as(nat64, 0x00000000);

    static const int32 PAX_FLOAT64_EXP_BIAS = pax_as(int32, 1023);
    static const int32 PAX_FLOAT64_EXP_MAX  = pax_as(int32, 1023);
    static const int32 PAX_FLOAT64_EXP_MIN  = pax_as(int32, -1022);
    static const int64 PAX_FLOAT64_EXP_SIZE = pax_as(int64, 11);
    static const nat64 PAX_FLOAT64_EXP_MASK = pax_as(nat64, 0x7ff0000000000000);

    static const int64 PAX_FLOAT64_FRAC_SIZE = pax_as(int64, 52);
    static const nat64 PAX_FLOAT64_FRAC_MASK = pax_as(nat64, 0x000fffffffffffff);

    static const int64 PAX_FLOAT64_SIGN_SIZE = pax_as(int64, 1);
    static const nat64 PAX_FLOAT64_SIGN_MASK = pax_as(nat64, 0x8000000000000000);

#endif

#if PAX_SIZE == PAX_SIZE_32

    typedef int32   Int;
    typedef nat32   Nat;
    typedef bool32  Bool;
    typedef float32 Float;

    #define PAX_INT_MAX PAX_INT32_MAX
    #define PAX_INT_MIN PAX_INT32_MIN

    #define PAX_NAT_MAX PAX_NAT32_MAX
    #define PAX_NAT_MIN PAX_NAT32_MIN

    #define PAX_FLOAT_EXP_BIAS  PAX_F32_EXP_BIAS
    #define PAX_FLOAT_EXP_MAX   PAX_F32_EXP_MAX
    #define PAX_FLOAT_EXP_MIN   PAX_F32_EXP_MIN
    #define PAX_FLOAT_EXP_SIZE  PAX_F32_EXP_SIZE
    #define PAX_FLOAT_EXP_MASK  PAX_F32_EXP_MASK

    #define PAX_FLOAT_FRAC_SIZE PAX_F32_FRAC_SIZE
    #define PAX_FLOAT_FRAC_MASK PAX_F32_FRAC_MASK

    #define PAX_FLOAT_SIGN_SIZE PAX_F32_SIGN_SIZE
    #define PAX_FLOAT_SIGN_MASK PAX_F32_SIGN_MASK

#elif PAX_SIZE == PAX_SIZE_64

    typedef int64   Int;
    typedef nat64   Nat;
    typedef bool64  Bool;
    typedef float64 Float;

    #define PAX_INT_MAX PAX_INT64_MAX
    #define PAX_INT_MIN PAX_INT64_MIN

    #define PAX_NAT_MAX PAX_NAT64_MAX
    #define PAX_NAT_MIN PAX_NAT64_MIN

    #define PAX_FLOAT_EXP_BIAS  PAX_FLOAT64_EXP_BIAS
    #define PAX_FLOAT_EXP_MAX   PAX_FLOAT64_EXP_MAX
    #define PAX_FLOAT_EXP_MIN   PAX_FLOAT64_EXP_MIN
    #define PAX_FLOAT_EXP_SIZE  PAX_FLOAT64_EXP_SIZE
    #define PAX_FLOAT_EXP_MASK  PAX_FLOAT64_EXP_MASK

    #define PAX_FLOAT_FRAC_SIZE PAX_FLOAT64_FRAC_SIZE
    #define PAX_FLOAT_FRAC_MASK PAX_FLOAT64_FRAC_MASK

    #define PAX_FLOAT_SIGN_SIZE PAX_FLOAT64_SIGN_SIZE
    #define PAX_FLOAT_SIGN_MASK PAX_FLOAT64_SIGN_MASK

#else

    #error "Unknown platform"

#endif

//
// Values
//

//
// Procs
//

/* Integer absolute value */

Nat
pax_abs_int(Int value);

nat64
pax_abs_int64(int64 value);

nat32
pax_abs_int32(int32 value);

nat16
pax_abs_int16(int16 value);

nat8
pax_abs_int8(int8 value);

/* Floating absolute value */

Float
pax_abs_float(Float value);

float64
pax_abs_float64(float64 value);

float32
pax_abs_float32(float32 value);

/* Integer sign */

bool8
pax_sig_int(Int value);

bool8
pax_sig_int64(int64 value);

bool8
pax_sig_int32(int32 value);

bool8
pax_sig_int16(int16 value);

bool8
pax_sig_int8(int8 value);

/* Floating sign */

bool8
pax_sig_float(Float value);

bool8
pax_sig_float64(float64 value);

bool8
pax_sig_float32(float32 value);

#endif // PAX_BASE_NUMBER_H
