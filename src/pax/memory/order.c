#ifndef PX_MEMORY_BYTE_ORDER_C
#define PX_MEMORY_BYTE_ORDER_C

#include "order.h"

PxByteOrder
pxByteOrder()
{
    pxword16 word = 0x0001;

    switch (pxCast(pxword8*, &word)[0]) {
        case 0:
            return PX_BYTE_ORDER_NETWORK;

        case 1:
            return PX_BYTE_ORDER_REVERSE;

        default: break;
    }

    return PX_BYTE_ORDER_NONE;
}

void*
pxMemoryNetFromLocal(void* memory, pxint length, pxint stride)
{
    if (pxByteOrder() == PX_BYTE_ORDER_REVERSE)
        return pxMemoryFlip(memory, length, stride);

    return memory;
}

void*
pxMemoryNetCopyLocal(void* memory, void* value, pxint length, pxint stride)
{
    if (pxByteOrder() == PX_BYTE_ORDER_REVERSE)
        return pxMemoryCopyFlipped(memory, value, length, stride);

    return pxMemoryCopy(memory, value, length, stride);
}

pxword16
pxWord16NetFromLocal(pxword16 value)
{
    pxword16 result = 0;

    pxMemoryNetCopyLocal(&result,
        &value, 2, 1);

    return result;
}

pxword32
pxWord32NetFromLocal(pxword32 value)
{
    pxword32 result = 0;

    pxMemoryNetCopyLocal(&result,
        &value, 4, 1);

    return result;
}

pxword64
pxWord64NetFromLocal(pxword64 value)
{
    pxword64 result = 0;

    pxMemoryNetCopyLocal(&result,
        &value, 8, 1);

    return result;
}

pxword16
pxInt16NetFromLocal(pxint16 value)
{
    pxword16 result = 0;

    pxMemoryNetCopyLocal(&result,
        &value, 2, 1);

    return result;
}

pxword32
pxInt32NetFromLocal(pxint32 value)
{
    pxword32 result = 0;

    pxMemoryNetCopyLocal(&result,
        &value, 4, 1);

    return result;
}

pxword64
pxInt64NetFromLocal(pxint64 value)
{
    pxword64 result = 0;

    pxMemoryNetCopyLocal(&result,
        &value, 8, 1);

    return result;
}

pxword32
pxFloat32NetFromLocal(pxfloat32 value)
{
    pxword32 result = 0;

    pxMemoryNetCopyLocal(&result,
        &value, 4, 1);

    return result;
}

pxword64
pxFloat64NetFromLocal(pxfloat64 value)
{
    pxword64 result = 0;

    pxMemoryNetCopyLocal(&result,
        &value, 8, 1);

    return result;
}

void*
pxMemoryLocalFromNet(void* memory, pxint length, pxint stride)
{
    if (pxByteOrder() == PX_BYTE_ORDER_REVERSE)
        return pxMemoryFlip(memory, length, stride);

    return memory;
}

void*
pxMemoryLocalCopyNet(void* memory, void* value, pxint length, pxint stride)
{
    if (pxByteOrder() == PX_BYTE_ORDER_REVERSE)
        return pxMemoryCopyFlipped(memory, value, length, stride);

    return pxMemoryCopy(memory, value, length, stride);
}

pxword16
pxWord16LocalFromNet(pxword16 value)
{
    pxword16 result = 0;

    pxMemoryLocalCopyNet(&result,
        &value, 2, 1);

    return result;
}

pxword32
pxWord32LocalFromNet(pxword32 value)
{
    pxword32 result = 0;

    pxMemoryLocalCopyNet(&result,
        &value, 4, 1);

    return result;
}

pxword64
pxWord64LocalFromNet(pxword64 value)
{
    pxword64 result = 0;

    pxMemoryLocalCopyNet(&result,
        &value, 8, 1);

    return result;
}

pxint16
pxInt16LocalFromNet(pxword16 value)
{
    pxint16 result = 0;

    pxMemoryLocalCopyNet(&result,
        &value, 2, 1);

    return result;
}

pxint32
pxInt32LocalFromNet(pxword32 value)
{
    pxint32 result = 0;

    pxMemoryLocalCopyNet(&result,
        &value, 4, 1);

    return result;
}

pxint64
pxInt64LocalFromNet(pxword64 value)
{
    pxint64 result = 0;

    pxMemoryLocalCopyNet(&result,
        &value, 8, 1);

    return result;
}

pxfloat32
pxFloat32LocalFromNet(pxword32 value)
{
    pxfloat32 result = 0;

    pxMemoryLocalCopyNet(&result,
        &value, 4, 1);

    return result;
}

pxfloat64
pxFloat64LocalFromNet(pxword64 value)
{
    pxfloat64 result = 0;

    pxMemoryLocalCopyNet(&result,
        &value, 8, 1);

    return result;
}

#endif // PX_MEMORY_BYTE_ORDER_C
