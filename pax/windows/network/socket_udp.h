#ifndef PX_WINDOWS_NETWORK_SOCKET_UDP_H
#define PX_WINDOWS_NETWORK_SOCKET_UDP_H

#include "import.h"

typedef struct PxWindowsSocketUdp PxWindowsSocketUdp;

PxWindowsSocketUdp*
pxWindowsSocketUdpCreate(PxArena* arena, PxAddrType type);

void
pxWindowsSocketUdpDestroy(PxWindowsSocketUdp* self);

PxAddr
pxWindowsSocketUdpGetAddr(PxWindowsSocketUdp* self);

pxu16
pxWindowsSocketUdpGetPort(PxWindowsSocketUdp* self);

pxb8
pxWindowsSocketUdpBind(PxWindowsSocketUdp* self, PxAddr addr, pxu16 port);

pxb8
pxWindowsSocketUdpListen(PxWindowsSocketUdp* self);

pxb8
pxWindowsSocketUdpConnect(PxWindowsSocketUdp* self, PxAddr addr, pxu16 port);

PxWindowsSocketUdp*
pxWindowsSocketUdpAccept(PxWindowsSocketUdp* self, PxArena* arena);

pxiword
pxWindowsSocketUdpWriteMemory8(PxWindowsSocketUdp* self, pxu8* memory, pxiword length);

pxiword
pxWindowsSocketUdpWriteMemory8Host(PxWindowsSocketUdp* self, pxu8* memory, pxiword length, PxAddr addr, pxu16 port);

pxiword
pxWindowsSocketUdpReadMemory8(PxWindowsSocketUdp* self, pxu8* memory, pxiword length);

pxiword
pxWindowsSocketUdpReadMemory8Host(PxWindowsSocketUdp* self, pxu8* memory, pxiword length, PxAddr* addr, pxu16* port);

#endif // PX_WINDOWS_NETWORK_SOCKET_UDP_H
