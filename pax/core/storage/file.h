#ifndef PX_STORAGE_FILE_H
#define PX_STORAGE_FILE_H

#include "attribute.h"

typedef void* PxFile;

PxFile
pxFileCreate(PxArena* arena, PxString8 base, PxString8 name, PxFileMode mode);

PxFile
pxFileOpen(PxArena* arena, PxString8 base, PxString8 name, PxFileMode mode);

void
pxFileClose(PxFile self);

pxb8
pxFileDelete(PxArena* arena, PxString8 base, PxString8 name);

#endif // PX_STORAGE_FILE_H
