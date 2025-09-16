#ifndef PX_CORE_NETWORK_ADDRESS_H
#define PX_CORE_NETWORK_ADDRESS_H

#include "address_ip4.h"
#include "address_ip6.h"

typedef enum PxAddressType
{
    PX_ADDRESS_TYPE_NONE,
    PX_ADDRESS_TYPE_IP4,
    PX_ADDRESS_TYPE_IP6,
}
PxAddressType;

typedef struct PxAddress
{
    PxAddressType type;

    union
    {
        PxAddressIp4 ip4;
        PxAddressIp6 ip6;
    };
}
PxAddress;

PxAddress
pxAddressAny(PxAddressType type);

PxAddress
pxAddressLocalhost(PxAddressType type);

pxb8
pxAddressFromString8(PxString8 string, PxAddress* self, PxAddressType type);

pxb8
pxAddressIsEqual(PxAddress self, PxAddress value);

#endif // PX_CORE_NETWORK_ADDRESS_H
