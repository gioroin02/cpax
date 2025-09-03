#ifndef PX_STORAGE_SYSTEM_C
#define PX_STORAGE_SYSTEM_C

#include "directory.h"

#if PX_SYSTEM == PX_SYSTEM_WINDOWS

    #include "../../windows/storage/directory.c"

    #define __pxStorageCurrentDirectoryList__ pxWindowsStorageCurrentDirectoryList
    #define __pxStorageCurrentDirectory__     pxWindowsStorageCurrentDirectory

#elif PX_SYSTEM == PX_SYSTEM_LINUX

    #include "../../linux/storage/directory.c"

    #define __pxStorageCurrentDirectoryList__ pxLinuxStorageCurrentDirectoryList
    #define __pxStorageCurrentDirectory__     pxLinuxStorageCurrentDirectory

#else

    #error "Unknown platform"

#endif

PxStringList
pxStorageCurrentDirectoryList(PxArena* arena)
{
    return __pxStorageCurrentDirectoryList__(arena);
}

PxString8
pxStorageCurrentDirectory(PxArena* arena)
{
    return __pxStorageCurrentDirectory__(arena);
}

#endif // PX_STORAGE_SYSTEM_C
