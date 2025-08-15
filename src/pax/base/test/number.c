#include "../export.h"

#include <stdio.h>

int
main(int argc, char** argv)
{
    pxb8  dir0 = pxDirectionFloat32(-1.56);
    pxf32 mag0 = pxMagnitudeFloat32(-1.56);

    pxb8  dir1 = pxDirectionFloat32(mag0);
    pxf32 mag1 = pxMagnitudeFloat32(mag0);

    printf("%u, %f\n%u, %f\n",
        dir0, mag0, dir1, mag1);
}
