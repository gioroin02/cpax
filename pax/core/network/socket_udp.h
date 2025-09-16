#ifndef PX_CORE_NETWORK_SOCKET_UDP_H
#define PX_CORE_NETWORK_SOCKET_UDP_H

#include "address.h"

typedef void* PxSocketUdp;

PxSocketUdp
pxSocketUdpCreate(PxArena* arena, PxAddressType type);

void
pxSocketUdpDestroy(PxSocketUdp self);

PxAddress
pxSocketUdpGetAddress(PxSocketUdp self);

pxu16
pxSocketUdpGetPort(PxSocketUdp self);

pxb8
pxSocketUdpBind(PxSocketUdp self, PxAddress address, pxu16 port);

pxb8
pxSocketUdpListen(PxSocketUdp self);

pxb8
pxSocketUdpConnect(PxSocketUdp self, PxAddress address, pxu16 port);

PxSocketUdp
pxSocketUdpAccept(PxSocketUdp self, PxArena* arena);

pxiword
pxSocketUdpWriteMemory8(PxSocketUdp self, pxu8* memory, pxiword length);

pxiword
pxSocketUdpWriteHostMemory8(PxSocketUdp self, pxu8* memory, pxiword length, PxAddress address, pxu16 port);

pxiword
pxSocketUdpReadMemory8(PxSocketUdp self, pxu8* memory, pxiword length);

pxiword
pxSocketUdpReadHostMemory8(PxSocketUdp self, pxu8* memory, pxiword length, PxAddress* address, pxu16* port);

PxInput
pxInputFromSocketUdp(PxSocketUdp self);

PxOutput
pxOutputFromSocketUdp(PxSocketUdp self);

#endif // PX_CORE_NETWORK_SOCKET_UDP_H
