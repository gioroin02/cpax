#ifndef PX_WINDOWS_STORAGE_FILE_H
#define PX_WINDOWS_STORAGE_FILE_H

#include "import.h"

typedef struct PxWindowsFile PxWindowsFile;

PxWindowsFile*
pxWindowsFileCreate(PxArena* arena, PxString8 base, PxString8 name, PxFileMode mode);

PxWindowsFile*
pxWindowsFileOpen(PxArena* arena, PxString8 base, PxString8 name, PxFileMode mode);

void
pxWindowsFileClose(PxWindowsFile* self);

pxb8
pxWindowsFileDelete(PxArena* arena, PxString8 base, PxString8 name);

#endif // PX_WINDOWS_STORAGE_FILE_H
