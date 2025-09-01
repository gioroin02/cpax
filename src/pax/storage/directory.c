#ifndef PX_STORAGE_SYSTEM_C
#define PX_STORAGE_SYSTEM_C

#include "directory.h"

#if PX_SYSTEM == PX_SYSTEM_WINDOWS

    #include "../../windows/storage/directory.c"

    #define __pxStorageCurrentDirectory__ pxWindowsStorageCurrentDirectory

#elif PX_SYSTEM == PX_SYSTEM_LINUX

    #include "../../linux/storage/directory.c"

    #define __pxStorageCurrentDirectory__ pxLinuxStorageCurrentDirectory

#else

    #error "Unknown platform"

#endif

PxPath
pxStorageCurrentDirectory(PxArena* arena)
{
    return __pxStorageCurrentDirectory__(arena);
}

PxString8
pxStorageCurrentDirectoryName(PxArena* arena)
{
    PxPath path = pxStorageCurrentDirectory(arena);

    PxString8 string =
        pxString8FromPath(arena, &path, pxs8("/"));

    return string;
}

#endif // PX_STORAGE_SYSTEM_C
