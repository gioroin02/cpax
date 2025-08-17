#ifndef PX_WINDOWS_NETWORK_SOCKET_UDP_C
#define PX_WINDOWS_NETWORK_SOCKET_UDP_C

#include "import.h"

#define NOMINMAX
#define NOGDI
#define WIN32_LEAN_AND_MEAN

#include <winsock2.h>
#include <ws2tcpip.h>

typedef struct sockaddr_storage PxSockUdpData;
typedef struct sockaddr         PxSockUdpAddr;
typedef struct sockaddr_in      PxSockUdpIp4;
typedef struct sockaddr_in6     PxSockUdpIp6;

#define PX_SOCK_UDP_DATA_SIZE pxSize(PxSockUdpData)
#define PX_SOCK_UDP_IP4_SIZE  pxSize(PxSockUdpIp4)
#define PX_SOCK_UDP_IP6_SIZE  pxSize(PxSockUdpIp6)

#define pxSockUdpAddr(x) pxCast(PxSockUdpAddr*, x)
#define pxSockUdpIp4(x)  pxCast(PxSockUdpIp4*, x)
#define pxSockUdpIp6(x)  pxCast(PxSockUdpIp6*, x)

#define pxSockUdpIp4Addr(x) pxCast(void*,     &pxSockUdpIp4(&x)->sin_addr.s_addr)
#define pxSockUdpIp4Port(x) pxCast(pxword16*, &pxSockUdpIp4(&x)->sin_port)

#define pxSockUdpIp6Addr(x) pxCast(void*,     pxSockUdpIp6(&x)->sin6_addr.s6_addr)
#define pxSockUdpIp6Port(x) pxCast(pxword16*, &pxSockUdpIp6(&x)->sin6_port)

typedef struct PxWindowsSocketUdp
{
    SOCKET        handle;
    PxSockUdpData address;
}
PxWindowsSocketUdp;

PxWindowsSocketUdp*
pxWindowsSocketUdpCreate(PxArena* arena, PxAddressType type)
{
    pxint offset = pxArenaOffset(arena);
    pxint family = 0;

    switch (type) {
        case PX_ADDRESS_TYPE_IP4: family = AF_INET;  break;
        case PX_ADDRESS_TYPE_IP6: family = AF_INET6; break;

        default: return 0;
    }

    PxWindowsSocketUdp* result =
        pxArenaReserve(arena, PxWindowsSocketUdp, 1);

    if (result != 0) {
        result->handle  = socket(family, SOCK_DGRAM, 0);
        result->address = (PxSockUdpData) {.ss_family = family};

        if (result->handle != INVALID_SOCKET)
            return result;

        pxArenaRewind(arena, offset);
    }

    return 0;
}

void
pxWindowsSocketUdpDestroy(PxWindowsSocketUdp* self)
{
    if (self == 0) return;

    if (self->handle != INVALID_SOCKET)
        closesocket(self->handle);

    self->handle  = INVALID_SOCKET;
    self->address = (PxSockUdpData) {0};
}

PxAddress
pxWindowsSocketUdpGetAddress(PxWindowsSocketUdp* self)
{
    PxAddress result = {.type = PX_ADDRESS_TYPE_NONE};

    switch (self->address.ss_family) {
        case AF_INET:
            result.type = PX_ADDRESS_TYPE_IP4;

            pxMemoryCopy(&result.ip4.memory, pxSockUdpIp4Addr(self),
                PX_ADDRESS_IP4_GROUPS, 1);
        break;

        case AF_INET6:
            result.type = PX_ADDRESS_TYPE_IP6;

            pxMemoryCopy(&result.ip6.memory, pxSockUdpIp6Addr(self),
                PX_ADDRESS_IP6_GROUPS, 2);
        break;

        default: break;
    }

    return result;
}

pxword16
pxWindowsSocketUdpGetPort(PxWindowsSocketUdp* self)
{
    PxAddress result = {.type = PX_ADDRESS_TYPE_NONE};

    switch (self->address.ss_family) {
        case AF_INET:
            return *pxSockUdpIp4Port(self);

        case AF_INET6:
            return *pxSockUdpIp6Port(self);

        default: break;
    }

    return 0;
}

pxbool8
pxWindowsSocketUdpBind(PxWindowsSocketUdp* self, PxAddress address, pxword16 port)
{
    pxint family = 0;

    switch (address.type) {
        case PX_ADDRESS_TYPE_IP4: family = AF_INET;  break;
        case PX_ADDRESS_TYPE_IP6: family = AF_INET6; break;

        default: return 0;
    }

    if (self->address.ss_family != family) return 0;

    PxSockUdpData data = {0};
    pxint         size = 0;

    switch (address.type) {
        case PX_ADDRESS_TYPE_IP4:
            data = (PxSockUdpData) {.ss_family = AF_INET};
            size = PX_SOCK_UDP_IP4_SIZE;

            pxMemoryCopy(pxSockUdpIp4Addr(self),
                &address.ip4.memory, PX_ADDRESS_IP4_GROUPS, 1);

            pxMemoryNetCopyLocal(pxSockUdpIp4Port(self),
                &port, 1, 2);
        break;

        case PX_ADDRESS_TYPE_IP6:
            data = (PxSockUdpData) {.ss_family = AF_INET6};
            size = PX_SOCK_UDP_IP6_SIZE;

            pxMemoryCopy(pxSockUdpIp6Addr(self),
                &address.ip6.memory, PX_ADDRESS_IP6_GROUPS, 2);

            pxMemoryNetCopyLocal(pxSockUdpIp4Port(self),
                &port, 1, 2);
        break;

        default: return 0;
    }

    if (bind(self->handle, pxSockUdpAddr(&data), size) == SOCKET_ERROR)
        return 0;

    self->address = data;

    return 1;
}

void
pxWindowsSocketUdpListen(PxWindowsSocketUdp* self)
{
    listen(self->handle, SOMAXCONN);
}

pxbool8
pxWindowsSocketUdpConnect(PxWindowsSocketUdp* self, PxAddress address, pxword16 port)
{
    PxSockUdpData data = {0};
    pxint         size = 0;

    switch (address.type) {
        case PX_ADDRESS_TYPE_IP4:
            data = (PxSockUdpData) {.ss_family = AF_INET};
            size = PX_SOCK_UDP_IP4_SIZE;

            pxMemoryCopy(pxSockUdpIp4Addr(self),
                &address.ip4.memory, PX_ADDRESS_IP4_GROUPS, 1);

            pxMemoryNetCopyLocal(pxSockUdpIp4Port(self),
                &port, 1, 2);
        break;

        case PX_ADDRESS_TYPE_IP6:
            data = (PxSockUdpData) {.ss_family = AF_INET6};
            size = PX_SOCK_UDP_IP6_SIZE;

            pxMemoryCopy(pxSockUdpIp6Addr(self),
                &address.ip6.memory, PX_ADDRESS_IP6_GROUPS, 2);

            pxMemoryNetCopyLocal(pxSockUdpIp4Port(self),
                &port, 1, 2);
        break;

        default: return 0;
    }

    if (connect(self->handle, pxSockUdpAddr(&data), size) == SOCKET_ERROR)
        return 0;

    self->address = data;

    return 1;
}

PxWindowsSocketUdp*
pxWindowsSocketUdpAccept(PxWindowsSocketUdp* self, PxArena* arena)
{
    pxint offset = pxArenaOffset(arena);

    PxWindowsSocketUdp* result =
        pxArenaReserve(arena, PxWindowsSocketUdp, 1);

    if (result != 0) {
        PxSockUdpData data = {0};
        pxint         size = PX_SOCK_UDP_DATA_SIZE;

        result->handle = accept(self->handle,
            pxSockUdpAddr(&data), pxCast(int*, &size));

        result->address = data;

        if (result->handle != INVALID_SOCKET)
            return result;

        pxArenaRewind(arena, offset);
    }

    return 0;
}

pxint
pxWindowsSocketUdpWriteMemory(PxWindowsSocketUdp* self, pxword8* memory, pxint length)
{
    for (pxint i = 0; i < length;) {
        char* mem = pxCast(char*, memory + i);
        int   len = pxCast(int,   length + i);

        pxint amount = send(self->handle, mem, len, 0);

        if (amount > 0 && amount <= length - i)
            i += amount;
        else
            return i;
    }

    return length;
}

pxint
pxWindowsSocketUdpReadMemory(PxWindowsSocketUdp* self, pxword8* memory, pxint length)
{
    for (pxint i = 0; i < length;) {
        char* mem = pxCast(char*, memory + i);
        int   len = pxCast(int,   length + i);

        pxint amount = recv(self->handle, mem, len, 0);

        if (amount > 0 && amount <= length - i)
            i += amount;
        else
            return i;
    }

    return length;
}

#endif // PX_WINDOWS_NETWORK_SOCKET_UDP_C
