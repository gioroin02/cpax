#include "../export.h"

#include <stdio.h>

int
main(int argc, char** argv)
{
    pxi8  dir0 = pxDirectionFloat32(-1.56);
    pxf32 mag0 = pxMagnitudeFloat32(-1.56);

    printf("dir, mag = %i, %f\n", dir0, mag0);

    pxi8  dir1 = pxDirectionFloat32(+1.56);
    pxf32 mag1 = pxMagnitudeFloat32(+1.56);

    printf("dir, mag = %i, %f\n", dir1, mag1);

    pxi8  dir2 = pxDirectionFloat32(0);
    pxf32 mag2 = pxMagnitudeFloat32(0);

    printf("dir, mag = %i, %f\n", dir2, mag2);
}
