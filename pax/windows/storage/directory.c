#ifndef PX_WINDOWS_STORAGE_DIRECTORY_C
#define PX_WINDOWS_STORAGE_DIRECTORY_C

#include "directory.h"

#define NOMINMAX
#define NOGDI
#define WIN32_LEAN_AND_MEAN

#include <windows.h>

PxStringList
pxWindowsStorageCurrentDirectoryList(PxArena* arena)
{
    pxiword length = GetCurrentDirectoryW(0, 0);

    if (length <= 0) return (PxStringList) {0};

    pxiword offset = pxArenaOffset(arena);
    pxu16*  result = pxArenaReserve(arena, pxu16, length);

    PxString16 string = {.memory = result, .length = length};

    if (result != 0) {
        pxiword size = GetCurrentDirectoryW(length, result);

        if (size + 1 == length)
            return pxStringListFromString16(arena, string, pxs16(L"\\"));
    }

    pxArenaRewind(arena, offset);

    return (PxStringList) {0};
}

PxString8
pxWindowsStorageCurrentDirectory(PxArena* arena)
{
    PxStringList list =
        pxWindowsStorageCurrentDirectoryList(arena);

    return pxString8FromStringList(arena, &list,
        pxs8("/"), pxs8(""), pxs8(""));
}

#endif // PX_WINDOWS_STORAGE_DIRECTORY_C
