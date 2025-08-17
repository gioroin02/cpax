#ifndef PX_NETWORK_SOCKET_TCP_H
#define PX_NETWORK_SOCKET_TCP_H

#include "address.h"

typedef void* PxSocketTcp;

PxSocketTcp
pxSocketTcpCreate(PxArena* arena, PxAddressType type);

void
pxSocketTcpDestroy(PxSocketTcp self);

PxAddress
pxSocketTcpGetAddress(PxSocketTcp self);

pxword16
pxSocketTcpGetPort(PxSocketTcp self);

pxbool8
pxSocketTcpBind(PxSocketTcp self, PxAddress address, pxword16 port);

void
pxSocketTcpListen(PxSocketTcp self);

pxbool8
pxSocketTcpConnect(PxSocketTcp self, PxAddress address, pxword16 port);

PxSocketTcp
pxSocketTcpAccept(PxSocketTcp self, PxArena* arena);

pxint
pxSocketTcpWrite(PxSocketTcp self, PxBuffer8* buffer);

pxint
pxSocketTcpWriteMemory(PxSocketTcp self, pxword8* memory, pxint length);

pxint
pxSocketTcpRead(PxSocketTcp self, PxBuffer8* buffer);

pxint
pxSocketTcpReadMemory(PxSocketTcp self, pxword8* memory, pxint length);

PxReader
pxSocketTcpReader(PxSocketTcp self, PxBuffer8* buffer);

PxWriter
pxSocketTcpWriter(PxSocketTcp self, PxBuffer8* buffer);

#endif // PX_NETWORK_SOCKET_TCP_H
