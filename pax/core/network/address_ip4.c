#ifndef PX_CORE_NETWORK_ADDRESS_IP4_C
#define PX_CORE_NETWORK_ADDRESS_IP4_C

#include "address_ip4.h"

pxb8
pxAddressIp4FromString8(PxString8 string, PxAddressIp4* self)
{
    PxAddressIp4 temp = {0};

    pxiword groups = pxString8Contains(string, pxs8("."));

    if (groups != PX_ADDRESS_IP4_GROUPS - 1) return 0;

    PxString8 left  = {0};
    PxString8 right = string;

    for (pxiword i = 0; i < PX_ADDRESS_IP4_GROUPS; i += 1) {
        pxuword item = 0;

        pxString8Split(right, pxs8("."), &left, &right);

        if (pxUnsignedFromString8(left, &item, PX_FORMAT_RADIX_10, 0) == 0)
            return 0;

        if (item <= PX_U8_MAX)
            temp.items[i] = item;
        else
            return 0;
    }

    if (self != 0)
        pxMemoryCopy(self->items, temp.items, PX_ADDRESS_IP4_GROUPS, 1);

    return 1;
}

pxb8
pxAddressIp4IsEqual(PxAddressIp4 self, PxAddressIp4 value)
{
    return pxMemoryIsEqual(self.items, value.items,
        PX_ADDRESS_IP4_GROUPS, 1);
}

#endif // PX_CORE_NETWORK_ADDRESS_IP4_C
