#include "../export.h"

#include <stdio.h>

int
main(int argc, char** argv)
{
    pxbool8   dir0 = pxDirectionFloat32(-1.56);
    pxfloat32 mag0 = pxMagnitudeFloat32(-1.56);

    pxbool8   dir1 = pxDirectionFloat32(mag0);
    pxfloat32 mag1 = pxMagnitudeFloat32(mag0);

    printf("%u, %f\n%u, %f\n",
        dir0, mag0, dir1, mag1);
}
