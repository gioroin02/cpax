#ifndef PX_CORE_NETWORK_SOCKET_TCP_H
#define PX_CORE_NETWORK_SOCKET_TCP_H

#include "address.h"

typedef void* PxSocketTcp;

PxSocketTcp
pxSocketTcpCreate(PxArena* arena, PxAddressType type);

void
pxSocketTcpDestroy(PxSocketTcp self);

PxAddress
pxSocketTcpGetAddress(PxSocketTcp self);

pxu16
pxSocketTcpGetPort(PxSocketTcp self);

pxb8
pxSocketTcpBind(PxSocketTcp self, PxAddress address, pxu16 port);

pxb8
pxSocketTcpListen(PxSocketTcp self);

pxb8
pxSocketTcpConnect(PxSocketTcp self, PxAddress address, pxu16 port);

PxSocketTcp
pxSocketTcpAccept(PxSocketTcp self, PxArena* arena);

pxiword
pxSocketTcpWriteMemory8(PxSocketTcp self, pxu8* memory, pxiword length);

pxiword
pxSocketTcpReadMemory8(PxSocketTcp self, pxu8* memory, pxiword length);

PxInput
pxInputFromSocketTcp(PxSocketTcp self);

PxOutput
pxOutputFromSocketTcp(PxSocketTcp self);

#endif // PX_CORE_NETWORK_SOCKET_TCP_H
