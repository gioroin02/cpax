#ifndef PX_NETWORK_ADDRESS_IP6_C
#define PX_NETWORK_ADDRESS_IP6_C

#include "address_ip6.h"

pxbool8
pxAddressIp6FromString8(PxAddressIp6* self, PxString8 string)
{
    PxAddressIp6 temp = {0};

    PxFormatOptions options = pxFormatOptions(10,
        PX_FORMAT_FLAG_LEADING_ZERO);

    PxString8 left  = {0};
    PxString8 right = {0};
    PxString8 group = {0};

    switch (pxString8ContainsMemory(string, "::", 2)) {
        case 0:
            pxint groups = pxString8ContainsMemory(string, ":", 1);

            if (groups != PX_ADDRESS_IP6_GROUPS - 1) return 0;

            for (pxint i = 0; i < PX_ADDRESS_IP6_GROUPS; i += 1) {
                pxString8SplitMemory(string, ".", 1, &group, &string);

                if (pxWord16FromString8(&temp.memory[i], options, group) == 0)
                    return 0;
            }
        break;

        case 1:
            pxString8SplitMemory(string, "::", 2, &left, &right);

            pxint pivot = pxString8ContainsMemory(left, ":", 1) + 1;
            pxint start = 0;
            pxint stop  = PX_ADDRESS_IP6_GROUPS - 1;

            if (pivot >= stop) return 0;

            for (pxint i = start; i < pivot; i += 1) {
                pxString8SplitMemory(left, ":", 1, &group, &left);

                if (group.length <= 0) break;

                if (pxWord16FromString8(&temp.memory[i], options, group) == 0)
                    return 0;
            }

            start = pivot;
            pivot = pxString8ContainsMemory(right, ":", 1) + 1;

            if (start + pivot >= stop) return 0;

            for (pxint i = stop - pivot; i < stop; i += 1) {
                pxString8SplitMemory(right, ":", 1, &group, &right);

                if (group.length <= 0) break;

                if (pxWord16FromString8(&temp.memory[i], options, group) == 0)
                    return 0;
            }
        break;

        default: return 0;
    }

    if (self != 0) {
        pxMemoryCopy(self->memory, temp.memory,
            PX_ADDRESS_IP6_GROUPS, 2);
    }

    return 1;
}

pxbool8
pxAddressIp6IsEqual(PxAddressIp6 self, PxAddressIp6 value)
{
    return pxMemoryIsEqual(self.memory, value.memory,
        PX_ADDRESS_IP6_GROUPS, 2);
}

#endif // PX_NETWORK_ADDRESS_IP6_C
