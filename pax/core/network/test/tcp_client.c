#include "../export.h"

#include <stdio.h>

#define RED(x) "\x1b[31m" x "\x1b[0m"
#define GRN(x) "\x1b[32m" x "\x1b[0m"
#define YLW(x) "\x1b[33m" x "\x1b[0m"
#define BLU(x) "\x1b[34m" x "\x1b[0m"
#define MAG(x) "\x1b[35m" x "\x1b[0m"
#define CYA(x) "\x1b[36m" x "\x1b[0m"

#define FATAL MAG("FATAL")
#define ERROR RED("ERROR")
#define WARN  YLW("WARN")
#define INFO  BLU("INFO")
#define DEBUG GRN("DEBUG")
#define TRACE CYA("TRACE")

#define CLIENT_MSG pxs8("Hello server!")

#define CLIENT_ARG_IPV4 pxs8("--server-ipv4=")
#define CLIENT_ARG_IPV6 pxs8("--server-ipv6=")
#define CLIENT_ARG_PORT pxs8("--server-port=")

typedef struct ClientConfig
{
    PxAddr  addr;
    pxuword port;
}
ClientConfig;

typedef struct Client
{
    PxSocketTcp socket;

    PxBuffer8 request;
    PxBuffer8 response;
}
Client;

int
main(int argc, char** argv)
{
    PxArena arena = pxMemoryReserve(16);

    if (pxNetworkStart() == 0) return 1;

    ClientConfig config = {
        .addr = pxAddrLocalhost(PX_ADDR_TYPE_IP4),
        .port = 8000,
    };

    if (argc > 1) {
        for (pxiword i = 1; i < argc; i += 1) {
            PxString8 arg = pxString8FromMemory(argv[i], 32);

            if (pxString8BeginsWith(arg, CLIENT_ARG_IPV4) != 0) {
                arg = pxString8TrimPrefix(arg, CLIENT_ARG_IPV4);
                arg = pxString8TrimSpaces(arg);

                pxAddrFromString8(arg, &config.addr, PX_ADDR_TYPE_IP4);
            }

            if (pxString8BeginsWith(arg, CLIENT_ARG_IPV6) != 0) {
                arg = pxString8TrimPrefix(arg, CLIENT_ARG_IPV6);
                arg = pxString8TrimSpaces(arg);

                pxAddrFromString8(arg, &config.addr, PX_ADDR_TYPE_IP6);
            }

            if (pxString8BeginsWith(arg, CLIENT_ARG_PORT) != 0) {
                arg = pxString8TrimPrefix(arg, CLIENT_ARG_PORT);
                arg = pxString8TrimSpaces(arg);

                pxUnsignedFromString8(arg, &config.port, PX_FORMAT_RADIX_10, 0);
            }
        }
    }

    Client client = {0};

    client.socket = pxSocketTcpCreate(&arena, config.addr.type);

    if (client.socket == 0) return 1;

    if (pxSocketTcpConnect(client.socket, config.addr, config.port) == 0)
        return 1;

    client.request  = pxBuffer8Reserve(&arena, PX_MEMORY_KIB);
    client.response = pxBuffer8Reserve(&arena, PX_MEMORY_KIB);

    PxReader reader = pxReaderFromSocketTcp(client.socket);
    PxWriter writer = pxWriterFromSocketTcp(client.socket);

    pxBuffer8WriteString8Tail(&client.request, CLIENT_MSG);

    pxWriteBuffer8(writer, &client.request);

    pxiword size = pxReadBuffer8(reader, &client.response);

    if (size != 0) {
        PxString8 string = pxBuffer8ReadString8Head(
            &client.response, &arena, client.response.size);

        printf(INFO " " BLU("'%s'") "\n", string.memory);
    }

    pxSocketTcpDestroy(client.socket);

    pxNetworkStop();
}
