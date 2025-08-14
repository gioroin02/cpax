#include "../export.h"

#include <stdio.h>

int
main(int argc, char** argv)
{
    bool8   s0 = pax_sig_float32(-1.56);
    float32 f0 = pax_abs_float32(-1.56);

    bool8   s1 = pax_sig_float32(f0);
    float32 f1 = pax_abs_float32(f0);

    printf("%u, %f\n%u, %f\n", s0, f0, s1, f1);
}
