#ifndef PX_WINDOWS_NETWORK_SOCKET_TCP_H
#define PX_WINDOWS_NETWORK_SOCKET_TCP_H

#include "import.h"

typedef struct PxWindowsSocketTcp;

PxWindowsSocketTcp*
pxWindowsSocketTcpCreate(PxArena* arena, PxAddressType type);

void
pxWindowsSocketTcpDestroy(PxWindowsSocketTcp* self);

PxAddress
pxWindowsSocketTcpGetAddress(PxWindowsSocketTcp* self);

pxu16
pxWindowsSocketTcpGetPort(PxWindowsSocketTcp* self);

pxb8
pxWindowsSocketTcpBind(PxWindowsSocketTcp* self, PxAddress address, pxu16 port);

void
pxWindowsSocketTcpListen(PxWindowsSocketTcp* self);

pxb8
pxWindowsSocketTcpConnect(PxWindowsSocketTcp* self, PxAddress address, pxu16 port);

PxWindowsSocketTcp*
pxWindowsSocketTcpAccept(PxWindowsSocketTcp* self, PxArena* arena);

pxint
pxWindowsSocketTcpWriteMemory(PxWindowsSocketTcp* self, pxu8* memory, pxint length);

pxint
pxWindowsSocketTcpReadMemory(PxWindowsSocketTcp* self, pxu8* memory, pxint length);

#endif // PX_WINDOWS_NETWORK_SOCKET_TCP_H
