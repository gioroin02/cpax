#ifndef PX_CORE_NETWORK_SOCKET_TCP_C
#define PX_CORE_NETWORK_SOCKET_TCP_C

#include "socket_tcp.h"

#if PX_SYSTEM == PX_SYSTEM_WINDOWS

    #include "../../windows/network/socket_tcp.c"

    #define __pxSocketTcpCreate__       pxWindowsSocketTcpCreate
    #define __pxSocketTcpDestroy__      pxWindowsSocketTcpDestroy
    #define __pxSocketTcpGetAddr__      pxWindowsSocketTcpGetAddr
    #define __pxSocketTcpGetPort__      pxWindowsSocketTcpGetPort
    #define __pxSocketTcpBind__         pxWindowsSocketTcpBind
    #define __pxSocketTcpListen__       pxWindowsSocketTcpListen
    #define __pxSocketTcpConnect__      pxWindowsSocketTcpConnect
    #define __pxSocketTcpAccept__       pxWindowsSocketTcpAccept
    #define __pxSocketTcpWriteMemory8__ pxWindowsSocketTcpWriteMemory8
    #define __pxSocketTcpReadMemory8__  pxWindowsSocketTcpReadMemory8

#elif PX_SYSTEM == PX_SYSTEM_LINUX

    #include "../../linux/network/socket_tcp.c"

    #define __pxSocketTcpCreate__       pxLinuxSocketTcpCreate
    #define __pxSocketTcpDestroy__      pxLinuxSocketTcpDestroy
    #define __pxSocketTcpGetAddr__      pxLinuxSocketTcpGetAddr
    #define __pxSocketTcpGetPort__      pxLinuxSocketTcpGetPort
    #define __pxSocketTcpBind__         pxLinuxSocketTcpBind
    #define __pxSocketTcpListen__       pxLinuxSocketTcpListen
    #define __pxSocketTcpConnect__      pxLinuxSocketTcpConnect
    #define __pxSocketTcpAccept__       pxLinuxSocketTcpAccept
    #define __pxSocketTcpWriteMemory8__ pxLinuxSocketTcpWriteMemory8
    #define __pxSocketTcpReadMemory8__  pxLinuxSocketTcpReadMemory8

#else

    #error "Unknown platform"

#endif

PxSocketTcp
pxSocketTcpCreate(PxArena* arena, PxAddrType type)
{
    return __pxSocketTcpCreate__(arena, type);
}

void
pxSocketTcpDestroy(PxSocketTcp self)
{
    __pxSocketTcpDestroy__(self);
}

PxAddr
pxSocketTcpGetAddr(PxSocketTcp self)
{
    return __pxSocketTcpGetAddr__(self);
}

pxu16
pxSocketTcpGetPort(PxSocketTcp self)
{
    return __pxSocketTcpGetPort__(self);
}

pxb8
pxSocketTcpBind(PxSocketTcp self, PxAddr addr, pxu16 port)
{
    return __pxSocketTcpBind__(self, addr, port);
}

pxb8
pxSocketTcpListen(PxSocketTcp self)
{
    return __pxSocketTcpListen__(self);
}

pxb8
pxSocketTcpConnect(PxSocketTcp self, PxAddr addr, pxu16 port)
{
    return __pxSocketTcpConnect__(self, addr, port);
}

PxSocketTcp
pxSocketTcpAccept(PxSocketTcp self, PxArena* arena)
{
    return __pxSocketTcpAccept__(self, arena);
}

pxiword
pxSocketTcpWriteMemory8(PxSocketTcp self, pxu8* memory, pxiword length)
{
    return __pxSocketTcpWriteMemory8__(self, memory, length);
}

pxiword
pxSocketTcpReadMemory8(PxSocketTcp self, pxu8* memory, pxiword length)
{
    return __pxSocketTcpReadMemory8__(self, memory, length);
}

PxInput
pxInputFromSocketTcp(PxSocketTcp self)
{
    PxInput result = {0};

    if (self == 0) return result;

    result.ctxt = self;
    result.proc = &pxSocketTcpReadMemory8;

    return result;
}

PxOutput
pxOutputFromSocketTcp(PxSocketTcp self)
{
    PxOutput result = {0};

    if (self == 0) return result;

    result.ctxt = self;
    result.proc = &pxSocketTcpWriteMemory8;

    return result;
}

#endif // PX_CORE_NETWORK_SOCKET_TCP_C
