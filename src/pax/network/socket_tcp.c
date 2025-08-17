#ifndef PX_NETWORK_SOCKET_TCP_C
#define PX_NETWORK_SOCKET_TCP_C

#include "socket_tcp.h"

#if PX_SYSTEM == PX_SYSTEM_WINDOWS

    #include "../../windows/network/socket_tcp.c"

    #define __pxSocketTcpCreate__      pxWindowsSocketTcpCreate
    #define __pxSocketTcpDestroy__     pxWindowsSocketTcpDestroy
    #define __pxSocketTcpGetAddress__  pxWindowsSocketTcpGetAddress
    #define __pxSocketTcpGetPort__     pxWindowsSocketTcpGetPort
    #define __pxSocketTcpBind__        pxWindowsSocketTcpBind
    #define __pxSocketTcpListen__      pxWindowsSocketTcpListen
    #define __pxSocketTcpConnect__     pxWindowsSocketTcpConnect
    #define __pxSocketTcpAccept__      pxWindowsSocketTcpAccept
    #define __pxSocketTcpWriteMemory__ pxWindowsSocketTcpWriteMemory
    #define __pxSocketTcpReadMemory__  pxWindowsSocketTcpReadMemory

#else

    #error "Unknown platform"

#endif

PxSocketTcp
pxSocketTcpCreate(PxArena* arena, PxAddressType type)
{
    return __pxSocketTcpCreate__(arena, type);
}

void
pxSocketTcpDestroy(PxSocketTcp self)
{
    __pxSocketTcpDestroy__(self);
}

PxAddress
pxSocketTcpGetAddress(PxSocketTcp self)
{
    return __pxSocketTcpGetAddress__(self);
}

pxword16
pxSocketTcpGetPort(PxSocketTcp self)
{
    return __pxSocketTcpGetPort__(self);
}

pxbool8
pxSocketTcpBind(PxSocketTcp self, PxAddress address, pxword16 port)
{
    return __pxSocketTcpBind__(self, address, port);
}

void
pxSocketTcpListen(PxSocketTcp self)
{
    return __pxSocketTcpListen__(self);
}

pxbool8
pxSocketTcpConnect(PxSocketTcp self, PxAddress address, pxword16 port)
{
    return __pxSocketTcpConnect__(self, address, port);
}

PxSocketTcp
pxSocketTcpAccept(PxSocketTcp self, PxArena* arena)
{
    return __pxSocketTcpAccept__(self, arena);
}

pxint
pxSocketTcpWrite(PxSocketTcp self, PxBuffer8* buffer)
{
    pxBuffer8Normalize(buffer);

    pxword8* memory = buffer->memory;
    pxint    size   = buffer->size;

    if (size <= 0) return 0;

    pxint amount = __pxSocketTcpWriteMemory__(self, memory, size);

    buffer->size += amount;
    buffer->head  = (buffer->head + amount) % buffer->length;

    return amount;
}

pxint
pxSocketTcpWriteMemory(PxSocketTcp self, pxword8* memory, pxint length)
{
    return __pxSocketTcpWriteMemory__(self, memory, length);
}

pxint
pxSocketTcpRead(PxSocketTcp self, PxBuffer8* buffer)
{
    pxBuffer8Normalize(buffer);

    pxword8* memory = buffer->memory + buffer->size;
    pxint    size   = buffer->length - buffer->size;

    if (size <= 0) return 0;

    pxint amount = __pxSocketTcpReadMemory__(self, memory, size);

    buffer->size += amount;
    buffer->tail  = (buffer->tail + amount) % buffer->length;

    return amount;
}

pxint
pxSocketTcpReadMemory(PxSocketTcp self, pxword8* memory, pxint length)
{
    return __pxSocketTcpReadMemory__(self, memory, length);
}

PxWriter
pxSocketTcpWriter(PxSocketTcp self, PxBuffer8* buffer)
{
    if (self == 0 || buffer == 0)
        return (PxWriter) {0};

    return (PxWriter) {
        .buffer = buffer,
        .ctxt   = self,
        .proc   = &pxSocketTcpWrite,
    };
}

PxReader
pxSocketTcpReader(PxSocketTcp self, PxBuffer8* buffer)
{
    if (self == 0 || buffer == 0)
        return (PxReader) {0};

    return (PxReader) {
        .buffer = buffer,
        .ctxt   = self,
        .proc   = &pxSocketTcpRead,
    };
}

#endif // PX_NETWORK_SOCKET_TCP_C
