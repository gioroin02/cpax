#ifndef PX_MEMORY_BYTE_ORDER_H
#define PX_MEMORY_BYTE_ORDER_H

#include "import.h"

typedef enum
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
pxMemoryNetFromLocal(void* memory, pxint length, pxint stride);

void*
pxMemoryNetCopyLocal(void* memory, void* value, pxint length, pxint stride);

pxword16
pxWord16NetFromLocal(pxword16 value);

pxword32
pxWord32NetFromLocal(pxword32 value);

pxword64
pxWord64NetFromLocal(pxword64 value);

pxword16
pxInt16NetFromLocal(pxint16 value);

pxword32
pxInt32NetFromLocal(pxint32 value);

pxword64
pxInt64NetFromLocal(pxint64 value);

pxword32
pxFloat32NetFromLocal(pxfloat32 value);

pxword64
pxFloat64NetFromLocal(pxfloat64 value);

void*
pxMemoryLocalFromNet(void* memory, pxint length, pxint stride);

void*
pxMemoryLocalCopyNet(void* memory, void* value, pxint length, pxint stride);

pxword16
pxWord16LocalFromNet(pxword16 value);

pxword32
pxWord32LocalFromNet(pxword32 value);

pxword64
pxWord64LocalFromNet(pxword64 value);

pxint16
pxInt16LocalFromNet(pxword16 value);

pxint32
pxInt32LocalFromNet(pxword32 value);

pxint64
pxInt64LocalFromNet(pxword64 value);

pxfloat32
pxFloat32LocalFromNet(pxword32 value);

pxfloat64
pxFloat64LocalFromNet(pxword64 value);

#endif // PX_MEMORY_BYTE_ORDER_H
