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

pxword16
pxWindowsSocketTcpGetPort(PxWindowsSocketTcp* self);

pxbool8
pxWindowsSocketTcpBind(PxWindowsSocketTcp* self, PxAddress address, pxword16 port);

void
pxWindowsSocketTcpListen(PxWindowsSocketTcp* self);

pxbool8
pxWindowsSocketTcpConnect(PxWindowsSocketTcp* self, PxAddress address, pxword16 port);

PxWindowsSocketTcp*
pxWindowsSocketTcpAccept(PxWindowsSocketTcp* self, PxArena* arena);

pxint
pxWindowsSocketTcpWriteMemory(PxWindowsSocketTcp* self, pxword8* memory, pxint length);

pxint
pxWindowsSocketTcpReadMemory(PxWindowsSocketTcp* self, pxword8* memory, pxint length);

#endif // PX_WINDOWS_NETWORK_SOCKET_TCP_H
