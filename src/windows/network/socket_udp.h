#ifndef PX_WINDOWS_NETWORK_SOCKET_UDP_H
#define PX_WINDOWS_NETWORK_SOCKET_UDP_H

#include "import.h"

typedef struct PxWindowsSocketUdp;

PxWindowsSocketUdp*
pxWindowsSocketUdpCreate(PxArena* arena, PxAddressType type);

void
pxWindowsSocketUdpDestroy(PxWindowsSocketUdp* self);

PxAddress
pxWindowsSocketUdpGetAddress(PxWindowsSocketUdp* self);

pxword16
pxWindowsSocketUdpGetPort(PxWindowsSocketUdp* self);

pxbool8
pxWindowsSocketUdpBind(PxWindowsSocketUdp* self, PxAddress address, pxword16 port);

void
pxWindowsSocketUdpListen(PxWindowsSocketUdp* self);

pxbool8
pxWindowsSocketUdpConnect(PxWindowsSocketUdp* self, PxAddress address, pxword16 port);

PxWindowsSocketUdp*
pxWindowsSocketUdpAccept(PxWindowsSocketUdp* self, PxArena* arena);

pxint
pxWindowsSocketUdpWriteMemory(PxWindowsSocketUdp* self, pxword8* memory, pxint length);

pxint
pxWindowsSocketUdpReadMemory(PxWindowsSocketUdp* self, pxword8* memory, pxint length);

#endif // PX_WINDOWS_NETWORK_SOCKET_UDP_H
