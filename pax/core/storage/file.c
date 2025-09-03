#ifndef PX_STORAGE_FILE_C
#define PX_STORAGE_FILE_C

#include "file.h"

#if PX_SYSTEM == PX_SYSTEM_WINDOWS

    #include "../../windows/storage/file.c"

    #define __pxFileCreate__ pxWindowsFileCreate
    #define __pxFileOpen__   pxWindowsFileOpen
    #define __pxFileClose__  pxWindowsFileClose
    #define __pxFileDelete__ pxWindowsFileDelete

#elif PX_SYSTEM == PX_SYSTEM_LINUX

    #include "../../linux/storage/file.c"

    #define __pxFileCreate__ pxLinuxFileCreate
    #define __pxFileOpen__   pxLinuxFileOpen
    #define __pxFileClose__  pxLinuxFileClose
    #define __pxFileDelete__ pxLinuxFileDelete

#else

    #error "Unknown platform"

#endif

PxFile
pxFileCreate(PxArena* arena, PxString8 base, PxString8 name, PxFileMode mode)
{
    return __pxFileCreate__(arena, base, name, mode);
}

PxFile
pxFileOpen(PxArena* arena, PxString8 base, PxString8 name, PxFileMode mode)
{
    return __pxFileOpen__(arena, base, name, mode);
}

void
pxFileClose(PxFile self)
{
    __pxFileClose__(self);
}

pxb8
pxFileDelete(PxArena* arena, PxString8 base, PxString8 name)
{
    return __pxFileDelete__(arena, base, name);
}

#endif // PX_STORAGE_FILE_C
