#ifndef PX_NETWORK_SOCKET_UDP_H
#define PX_NETWORK_SOCKET_UDP_H

#include "address.h"

typedef void* PxSocketUdp;

PxSocketUdp
pxSocketUdpCreate(PxArena* arena, PxAddressType type);

void
pxSocketUdpDestroy(PxSocketUdp self);

PxAddress
pxSocketUdpGetAddress(PxSocketUdp self);

pxword16
pxSocketUdpGetPort(PxSocketUdp self);

pxbool8
pxSocketUdpBind(PxSocketUdp self, PxAddress address, pxword16 port);

void
pxSocketUdpListen(PxSocketUdp self);

pxbool8
pxSocketUdpConnect(PxSocketUdp self, PxAddress address, pxword16 port);

PxSocketUdp
pxSocketUdpAccept(PxSocketUdp self, PxArena* arena);

pxint
pxSocketUdpWrite(PxSocketUdp self, PxBuffer8* buffer);

pxint
pxSocketUdpWriteMemory(PxSocketUdp self, pxword8* memory, pxint length);

pxint
pxSocketUdpRead(PxSocketUdp self, PxBuffer8* buffer);

pxint
pxSocketUdpReadMemory(PxSocketUdp self, pxword8* memory, pxint length);

PxReader
pxSocketUdpReader(PxSocketUdp self, PxBuffer8* buffer);

PxWriter
pxSocketUdpWriter(PxSocketUdp self, PxBuffer8* buffer);

#endif // PX_NETWORK_SOCKET_UDP_H
