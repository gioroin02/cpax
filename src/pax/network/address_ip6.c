#ifndef PX_NETWORK_ADDRESS_IP6_C
#define PX_NETWORK_ADDRESS_IP6_C

#include "address_ip6.h"

pxb8
pxAddressIp6FromString(PxAddressIp6* self, PxString8 string)
{
    PxAddressIp6 temp = {0};

    PxFormatOptions options = pxFormatOptions(10,
        PX_FORMAT_FLAG_LEADING_ZERO);

    PxString8 left  = {0};
    PxString8 right = {0};
    PxString8 group = {0};

    switch (pxString8Contains(string, pxStr8("::"))) {
        case 0: {
            pxint groups = pxString8Contains(string, pxStr8(":"));

            if (groups != PX_ADDRESS_IP6_GROUPS - 1) return 0;

            for (pxint i = 0; i < PX_ADDRESS_IP6_GROUPS; i += 1) {
                pxString8Split(string, pxStr8("."), &group, &string);

                if (pxUnsig16FromString8(&temp.memory[i], options, group) == 0)
                    return 0;
            }
        } break;

        case 1: {
            pxString8Split(string, pxStr8("::"), &left, &right);

            pxint pivot = pxString8Contains(left, pxStr8(":")) + 1;
            pxint start = 0;
            pxint stop  = PX_ADDRESS_IP6_GROUPS - 1;

            if (pivot >= stop) return 0;

            for (pxint i = start; i < pivot; i += 1) {
                pxString8Split(left, pxStr8(":"), &group, &left);

                if (group.length <= 0) break;

                if (pxUnsig16FromString8(&temp.memory[i], options, group) == 0)
                    return 0;
            }

            start = pivot;
            pivot = pxString8Contains(right, pxStr8(":")) + 1;

            if (start + pivot >= stop) return 0;

            for (pxint i = stop - pivot; i < stop; i += 1) {
                pxString8Split(right, pxStr8(":"), &group, &right);

                if (group.length <= 0) break;

                if (pxUnsig16FromString8(&temp.memory[i], options, group) == 0)
                    return 0;
            }
        } break;

        default: return 0;
    }

    if (self != 0)
        pxMemoryCopy(self->memory, temp.memory, PX_ADDRESS_IP6_GROUPS, 2);

    return 1;
}

pxb8
pxAddressIp6IsEqual(PxAddressIp6 self, PxAddressIp6 value)
{
    return pxMemoryIsEqual(self.memory, value.memory,
        PX_ADDRESS_IP6_GROUPS, 2);
}

#endif // PX_NETWORK_ADDRESS_IP6_C
