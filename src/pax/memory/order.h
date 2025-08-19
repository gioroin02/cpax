#ifndef PX_MEMORY_BYTE_ORDER_H
#define PX_MEMORY_BYTE_ORDER_H

#include "import.h"

typedef enum PxByteOrder
{
    PX_BYTE_ORDER_NONE,
    PX_BYTE_ORDER_NETWORK,
    PX_BYTE_ORDER_REVERSE,
    PX_BYET_ORDER_COUNT,
}
PxByteOrder;

PxByteOrder
pxByteOrder();

void*
pxMemoryNetFromLocal(void* memory, pxint amount, pxint stride);

void*
pxMemoryNetCopyLocal(void* memory, void* value, pxint amount, pxint stride);

pxu16
pxUnsig16NetFromLocal(pxu16 value);

pxu32
pxUnsig32NetFromLocal(pxu32 value);

pxu64
pxUnsig64NetFromLocal(pxu64 value);

pxunsig
pxUnsigNetFromLocal(pxunsig value);

pxu16
pxInt16NetFromLocal(pxi16 value);

pxu32
pxInt32NetFromLocal(pxi32 value);

pxu64
pxInt64NetFromLocal(pxi64 value);

pxunsig
pxIntNetFromLocal(pxint value);

pxu32
pxFloat32NetFromLocal(pxf32 value);

pxu64
pxFloat64NetFromLocal(pxf64 value);

pxunsig
pxFloatNetFromLocal(pxfloat value);

void*
pxMemoryLocalFromNet(void* memory, pxint amount, pxint stride);

void*
pxMemoryLocalCopyNet(void* memory, void* value, pxint amount, pxint stride);

pxu16
pxUnsig16LocalFromNet(pxu16 value);

pxu32
pxUnsig32LocalFromNet(pxu32 value);

pxu64
pxUnsig64LocalFromNet(pxu64 value);

pxunsig
pxUnsigLocalFromNet(pxunsig value);

pxi16
pxInt16LocalFromNet(pxu16 value);

pxi32
pxInt32LocalFromNet(pxu32 value);

pxi64
pxInt64LocalFromNet(pxu64 value);

pxint
pxIntLocalFromNet(pxunsig value);

pxf32
pxFloat32LocalFromNet(pxu32 value);

pxf64
pxFloat64LocalFromNet(pxu64 value);

pxfloat
pxFloatLocalFromNet(pxunsig value);

#endif // PX_MEMORY_BYTE_ORDER_H
