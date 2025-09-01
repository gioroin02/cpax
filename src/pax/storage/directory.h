#ifndef PX_STORAGE_DIRECTORY_H
#define PX_STORAGE_DIRECTORY_H

#include "path.h"

PxPath
pxStorageCurrentDirectory(PxArena* arena);

PxString8
pxStorageCurrentDirectoryName(PxArena* arena);

#endif // PX_STORAGE_DIRECTORY_H
