#ifndef PX_CORE_NETWORK_SOCKET_UDP_C
#define PX_CORE_NETWORK_SOCKET_UDP_C

#include "socket_udp.h"

#if PX_SYSTEM == PX_SYSTEM_WINDOWS

    #include "../../windows/network/socket_udp.c"

    #define __pxSocketUdpCreate__           pxWindowsSocketUdpCreate
    #define __pxSocketUdpDestroy__          pxWindowsSocketUdpDestroy
    #define __pxSocketUdpGetAddress__       pxWindowsSocketUdpGetAddress
    #define __pxSocketUdpGetPort__          pxWindowsSocketUdpGetPort
    #define __pxSocketUdpBind__             pxWindowsSocketUdpBind
    #define __pxSocketUdpListen__           pxWindowsSocketUdpListen
    #define __pxSocketUdpConnect__          pxWindowsSocketUdpConnect
    #define __pxSocketUdpAccept__           pxWindowsSocketUdpAccept
    #define __pxSocketUdpWriteMemory8__     pxWindowsSocketUdpWriteMemory8
    #define __pxSocketUdpWriteHostMemory8__ pxWindowsSocketUdpWriteHostMemory8
    #define __pxSocketUdpReadMemory8__      pxWindowsSocketUdpReadMemory8
    #define __pxSocketUdpReadHostMemory8__  pxWindowsSocketUdpReadHostMemory8

#elif PX_SYSTEM == PX_SYSTEM_LINUX

    #include "../../linux/network/socket_udp.c"

    #define __pxSocketUdpCreate__           pxLinuxSocketUdpCreate
    #define __pxSocketUdpDestroy__          pxLinuxSocketUdpDestroy
    #define __pxSocketUdpGetAddress__       pxLinuxSocketUdpGetAddress
    #define __pxSocketUdpGetPort__          pxLinuxSocketUdpGetPort
    #define __pxSocketUdpBind__             pxLinuxSocketUdpBind
    #define __pxSocketUdpListen__           pxLinuxSocketUdpListen
    #define __pxSocketUdpConnect__          pxLinuxSocketUdpConnect
    #define __pxSocketUdpAccept__           pxLinuxSocketUdpAccept
    #define __pxSocketUdpWriteMemory8__     pxLinuxSocketUdpWriteMemory8
    #define __pxSocketUdpWriteHostMemory8__ pxLinuxSocketUdpWriteHostMemory8
    #define __pxSocketUdpReadMemory8__      pxLinuxSocketUdpReadMemory8
    #define __pxSocketUdpReadHostMemory8__  pxLinuxSocketUdpReadHostMemory8

#else

    #error "Unknown platform"

#endif

PxSocketUdp
pxSocketUdpCreate(PxArena* arena, PxAddressType type)
{
    return __pxSocketUdpCreate__(arena, type);
}

void
pxSocketUdpDestroy(PxSocketUdp self)
{
    __pxSocketUdpDestroy__(self);
}

PxAddress
pxSocketUdpGetAddress(PxSocketUdp self)
{
    return __pxSocketUdpGetAddress__(self);
}

pxu16
pxSocketUdpGetPort(PxSocketUdp self)
{
    return __pxSocketUdpGetPort__(self);
}

pxb8
pxSocketUdpBind(PxSocketUdp self, PxAddress address, pxu16 port)
{
    return __pxSocketUdpBind__(self, address, port);
}

pxb8
pxSocketUdpListen(PxSocketUdp self)
{
    return __pxSocketUdpListen__(self);
}

pxb8
pxSocketUdpConnect(PxSocketUdp self, PxAddress address, pxu16 port)
{
    return __pxSocketUdpConnect__(self, address, port);
}

PxSocketUdp
pxSocketUdpAccept(PxSocketUdp self, PxArena* arena)
{
    return __pxSocketUdpAccept__(self, arena);
}

pxiword
pxSocketUdpWriteMemory8(PxSocketUdp self, pxu8* memory, pxiword length)
{
    return __pxSocketUdpWriteMemory8__(self, memory, length);
}

pxiword
pxSocketUdpWriteHostMemory8(PxSocketUdp self, pxu8* memory, pxiword length, PxAddress address, pxu16 port)
{
    return __pxSocketUdpWriteHostMemory8__(self, memory, length, address, port);
}

pxiword
pxSocketUdpReadMemory8(PxSocketUdp self, pxu8* memory, pxiword length)
{
    return __pxSocketUdpReadMemory8__(self, memory, length);
}

pxiword
pxSocketUdpReadHostMemory8(PxSocketUdp self, pxu8* memory, pxiword length, PxAddress* address, pxu16* port)
{
    return __pxSocketUdpReadHostMemory8__(self, memory, length, address, port);
}

PxInput
pxInputFromSocketUdp(PxSocketUdp self)
{
    PxInput result = {0};

    if (self == 0) return result;

    result.ctxt = self;
    result.proc = &pxSocketUdpReadMemory8;

    return result;
}

PxOutput
pxOutputFromSocketUdp(PxSocketUdp self)
{
    PxOutput result = {0};

    if (self == 0) return result;

    result.ctxt = self;
    result.proc = &pxSocketUdpWriteMemory8;

    return result;
}

#endif // PX_CORE_NETWORK_SOCKET_UDP_C
