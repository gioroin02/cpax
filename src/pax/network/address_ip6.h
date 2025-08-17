#ifndef PX_NETWORK_ADDRESS_IP6_H
#define PX_NETWORK_ADDRESS_IP6_H

#include "import.h"

#define PX_ADDRESS_IP6_ANY       ((PxAddressIp6) {0})
#define PX_ADDRESS_IP6_LOCALHOST ((PxAddressIp6) {.h = 1})

#define PX_ADDRESS_IP6_GROUPS 8

typedef struct PxAddressIp6
{
    union
    {
        struct {
            pxword16 a, b, c, d;
            pxword16 e, f, g, h;
        };

        pxword16 memory[PX_ADDRESS_IP6_GROUPS];
    };
}
PxAddressIp6;

pxbool8
pxAddressIp6FromString8(PxAddressIp6* self, PxString8 string);

pxbool8
pxAddressIp6IsEqual(PxAddressIp6 self, PxAddressIp6 value);

#endif // PX_NETWORK_ADDRESS_IP6_H
