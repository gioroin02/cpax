#ifndef PX_CORE_NETWORK_SOCKET_UDP_C
#define PX_CORE_NETWORK_SOCKET_UDP_C

#include "socket_udp.h"

#if PX_SYSTEM == PX_SYSTEM_WINDOWS

    #include "../../windows/network/socket_udp.c"

    #define __pxSocketUdpCreate__           pxWindowsSocketUdpCreate
    #define __pxSocketUdpDestroy__          pxWindowsSocketUdpDestroy
    #define __pxSocketUdpGetAddr__          pxWindowsSocketUdpGetAddr
    #define __pxSocketUdpGetPort__          pxWindowsSocketUdpGetPort
    #define __pxSocketUdpBind__             pxWindowsSocketUdpBind
    #define __pxSocketUdpListen__           pxWindowsSocketUdpListen
    #define __pxSocketUdpConnect__          pxWindowsSocketUdpConnect
    #define __pxSocketUdpAccept__           pxWindowsSocketUdpAccept
    #define __pxSocketUdpWriteMemory8__     pxWindowsSocketUdpWriteMemory8
    #define __pxSocketUdpWriteMemory8Host__ pxWindowsSocketUdpWriteMemory8Host
    #define __pxSocketUdpReadMemory8__      pxWindowsSocketUdpReadMemory8
    #define __pxSocketUdpReadMemory8Host__  pxWindowsSocketUdpReadMemory8Host

#elif PX_SYSTEM == PX_SYSTEM_LINUX

    #include "../../linux/network/socket_udp.c"

    #define __pxSocketUdpCreate__           pxLinuxSocketUdpCreate
    #define __pxSocketUdpDestroy__          pxLinuxSocketUdpDestroy
    #define __pxSocketUdpGetAddr__          pxLinuxSocketUdpGetAddr
    #define __pxSocketUdpGetPort__          pxLinuxSocketUdpGetPort
    #define __pxSocketUdpBind__             pxLinuxSocketUdpBind
    #define __pxSocketUdpListen__           pxLinuxSocketUdpListen
    #define __pxSocketUdpConnect__          pxLinuxSocketUdpConnect
    #define __pxSocketUdpAccept__           pxLinuxSocketUdpAccept
    #define __pxSocketUdpWriteMemory8__     pxLinuxSocketUdpWriteMemory8
    #define __pxSocketUdpWriteMemory8Host__ pxLinuxSocketUdpWriteMemory8Host
    #define __pxSocketUdpReadMemory8__      pxLinuxSocketUdpReadMemory8
    #define __pxSocketUdpReadMemory8Host__  pxLinuxSocketUdpReadMemory8Host

#else

    #error "Unknown platform"

#endif

PxSocketUdp
pxSocketUdpCreate(PxArena* arena, PxAddrType type)
{
    return __pxSocketUdpCreate__(arena, type);
}

void
pxSocketUdpDestroy(PxSocketUdp self)
{
    __pxSocketUdpDestroy__(self);
}

PxAddr
pxSocketUdpGetAddr(PxSocketUdp self)
{
    return __pxSocketUdpGetAddr__(self);
}

pxu16
pxSocketUdpGetPort(PxSocketUdp self)
{
    return __pxSocketUdpGetPort__(self);
}

pxb8
pxSocketUdpBind(PxSocketUdp self, PxAddr addr, pxu16 port)
{
    return __pxSocketUdpBind__(self, addr, port);
}

pxb8
pxSocketUdpListen(PxSocketUdp self)
{
    return __pxSocketUdpListen__(self);
}

pxb8
pxSocketUdpConnect(PxSocketUdp self, PxAddr addr, pxu16 port)
{
    return __pxSocketUdpConnect__(self, addr, port);
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
pxSocketUdpWriteMemory8Host(PxSocketUdp self, pxu8* memory, pxiword length, PxAddr addr, pxu16 port)
{
    return __pxSocketUdpWriteMemory8Host__(self, memory, length, addr, port);
}

pxiword
pxSocketUdpReadMemory8(PxSocketUdp self, pxu8* memory, pxiword length)
{
    return __pxSocketUdpReadMemory8__(self, memory, length);
}

pxiword
pxSocketUdpReadMemory8Host(PxSocketUdp self, pxu8* memory, pxiword length, PxAddr* addr, pxu16* port)
{
    return __pxSocketUdpReadMemory8Host__(self, memory, length, addr, port);
}

PxReader
pxReaderFromSocketUdp(PxSocketUdp self)
{
    PxReader result = {0};

    if (self == 0) return result;

    result.ctxt = self;
    result.proc = &pxSocketUdpReadMemory8;

    return result;
}

PxWriter
pxWriterFromSocketUdp(PxSocketUdp self)
{
    PxWriter result = {0};

    if (self == 0) return result;

    result.ctxt = self;
    result.proc = &pxSocketUdpWriteMemory8;

    return result;
}

#endif // PX_CORE_NETWORK_SOCKET_UDP_C
