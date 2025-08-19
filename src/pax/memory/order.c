#ifndef PX_MEMORY_BYTE_ORDER_C
#define PX_MEMORY_BYTE_ORDER_C

#include "order.h"

PxByteOrder
pxByteOrder()
{
    pxu16 word = 0x0001;

    switch (pxCast(pxu8*, &word)[0]) {
        case 0:
            return PX_BYTE_ORDER_NETWORK;

        case 1:
            return PX_BYTE_ORDER_REVERSE;

        default: break;
    }

    return PX_BYTE_ORDER_NONE;
}

void*
pxMemoryNetFromLocal(void* memory, pxint amount, pxint stride)
{
    if (pxByteOrder() == PX_BYTE_ORDER_REVERSE)
        return pxMemoryFlip(memory, amount, stride);

    return memory;
}

void*
pxMemoryNetCopyLocal(void* memory, void* value, pxint amount, pxint stride)
{
    if (pxByteOrder() == PX_BYTE_ORDER_REVERSE)
        return pxMemoryCopyFlipped(memory, value, amount, stride);

    return pxMemoryCopy(memory, value, amount, stride);
}

pxu16
pxUnsig16NetFromLocal(pxu16 value)
{
    pxu16 result = 0;

    pxMemoryNetCopyLocal(&result,
        &value, 1, PX_U16_SIZE);

    return result;
}

pxu32
pxUnsig32NetFromLocal(pxu32 value)
{
    pxu32 result = 0;

    pxMemoryNetCopyLocal(&result,
        &value, 1, PX_U32_SIZE);

    return result;
}

pxu64
pxUnsig64NetFromLocal(pxu64 value)
{
    pxu64 result = 0;

    pxMemoryNetCopyLocal(&result,
        &value, 1, PX_U64_SIZE);

    return result;
}

pxunsig
pxUnsigNetFromLocal(pxunsig value)
{
    pxunsig result = 0;

    pxMemoryNetCopyLocal(&result,
        &value, 1, PX_UNSIG_SIZE);

    return result;
}

pxu16
pxInt16NetFromLocal(pxi16 value)
{
    pxu16 result = 0;

    pxMemoryNetCopyLocal(&result,
        &value, 1, PX_I16_SIZE);

    return result;
}

pxu32
pxInt32NetFromLocal(pxi32 value)
{
    pxu32 result = 0;

    pxMemoryNetCopyLocal(&result,
        &value, 1, PX_I32_SIZE);

    return result;
}

pxu64
pxInt64NetFromLocal(pxi64 value)
{
    pxu64 result = 0;

    pxMemoryNetCopyLocal(&result,
        &value, 1, PX_I64_SIZE);

    return result;
}

pxunsig
pxIntNetFromLocal(pxint value)
{
    pxunsig result = 0;

    pxMemoryNetCopyLocal(&result,
        &value, 1, PX_INT_SIZE);

    return result;
}

pxu32
pxFloat32NetFromLocal(pxf32 value)
{
    pxu32 result = 0;

    pxMemoryNetCopyLocal(&result,
        &value, 1, PX_F32_SIZE);

    return result;
}

pxu64
pxFloat64NetFromLocal(pxf64 value)
{
    pxu64 result = 0;

    pxMemoryNetCopyLocal(&result,
        &value, 1, PX_F64_SIZE);

    return result;
}

pxunsig
pxFloatNetFromLocal(pxfloat value)
{
    pxunsig result = 0;

    pxMemoryNetCopyLocal(&result,
        &value, 1, PX_FLOAT_SIZE);

    return result;
}

void*
pxMemoryLocalFromNet(void* memory, pxint amount, pxint stride)
{
    if (pxByteOrder() == PX_BYTE_ORDER_REVERSE)
        return pxMemoryFlip(memory, amount, stride);

    return memory;
}

void*
pxMemoryLocalCopyNet(void* memory, void* value, pxint amount, pxint stride)
{
    if (pxByteOrder() == PX_BYTE_ORDER_REVERSE)
        return pxMemoryCopyFlipped(memory, value, amount, stride);

    return pxMemoryCopy(memory, value, amount, stride);
}

pxu16
pxUnsig16LocalFromNet(pxu16 value)
{
    pxu16 result = 0;

    pxMemoryLocalCopyNet(&result,
        &value, 1, PX_U16_SIZE);

    return result;
}

pxu32
pxUnsig32LocalFromNet(pxu32 value)
{
    pxu32 result = 0;

    pxMemoryLocalCopyNet(&result,
        &value, 1, PX_U32_SIZE);

    return result;
}

pxu64
pxUnsig64LocalFromNet(pxu64 value)
{
    pxu64 result = 0;

    pxMemoryLocalCopyNet(&result,
        &value, 1, PX_U64_SIZE);

    return result;
}

pxunsig
pxUnsigLocalFromNet(pxunsig value)
{
    pxunsig result = 0;

    pxMemoryLocalCopyNet(&result,
        &value, 1, PX_UNSIG_SIZE);

    return result;
}

pxi16
pxInt16LocalFromNet(pxu16 value)
{
    pxi16 result = 0;

    pxMemoryLocalCopyNet(&result,
        &value, 1, PX_I64_SIZE);

    return result;
}

pxi32
pxInt32LocalFromNet(pxu32 value)
{
    pxi32 result = 0;

    pxMemoryLocalCopyNet(&result,
        &value, 1, PX_I32_SIZE);

    return result;
}

pxi64
pxInt64LocalFromNet(pxu64 value)
{
    pxi64 result = 0;

    pxMemoryLocalCopyNet(&result,
        &value, 1, PX_I64_SIZE);

    return result;
}

pxint
pxIntLocalFromNet(pxunsig value)
{
    pxint result = 0;

    pxMemoryLocalCopyNet(&result,
        &value, 1, PX_INT_SIZE);

    return result;
}

pxf32
pxFloat32LocalFromNet(pxu32 value)
{
    pxf32 result = 0;

    pxMemoryLocalCopyNet(&result,
        &value, 1, PX_F32_SIZE);

    return result;
}

pxf64
pxFloat64LocalFromNet(pxu64 value)
{
    pxf64 result = 0;

    pxMemoryLocalCopyNet(&result,
        &value, 1, PX_F64_SIZE);

    return result;
}

pxfloat
pxFloatLocalFromNet(pxunsig value)
{
    pxfloat result = 0;

    pxMemoryLocalCopyNet(&result,
        &value, 1, PX_FLOAT_SIZE);

    return result;
}

#endif // PX_MEMORY_BYTE_ORDER_C
