#ifndef PX_CORE_STORAGE_FILE_C
#define PX_CORE_STORAGE_FILE_C

#include "file.h"

#if PX_SYSTEM == PX_SYSTEM_WINDOWS

    #include "../../windows/storage/file.c"

    #define __pxStandardInput__  pxWindowsStandardInput
    #define __pxStandardOutput__ pxWindowsStandardOutput
    #define __pxStandardError__  pxWindowsStandardError

    #define __pxFileCreate__       pxWindowsFileCreate
    #define __pxFileReplace__      pxWindowsFileReplace
    #define __pxFileOpen__         pxWindowsFileOpen
    #define __pxFileClose__        pxWindowsFileClose
    #define __pxFileDestroy__      pxWindowsFileDestroy
    #define __pxFileDelete__       pxWindowsFileDelete
    #define __pxFileWriteMemory8__ pxWindowsFileWriteMemory8
    #define __pxFileReadMemory8__  pxWindowsFileReadMemory8

#elif PX_SYSTEM == PX_SYSTEM_LINUX

    #include "../../linux/storage/file.c"

    #define __pxStandardInput__  pxLinuxStandardInput
    #define __pxStandardOutput__ pxLinuxStandardOutput
    #define __pxStandardError__  pxLinuxStandardError

    #define __pxFileCreate__       pxLinuxFileCreate
    #define __pxFileReplace__      pxLinuxFileReplace
    #define __pxFileOpen__         pxLinuxFileOpen
    #define __pxFileClose__        pxLinuxFileClose
    #define __pxFileDestroy__      pxLinuxFileDestroy
    #define __pxFileDelete__       pxLinuxFileDelete
    #define __pxFileWriteMemory8__ pxLinuxFileWriteMemory8
    #define __pxFileReadMemory8__  pxLinuxFileReadMemory8

#else

    #error "Unknown platform"

#endif

PxFile
pxStandardInput(PxArena* arena)
{
    return __pxStandardInput__(arena);
}

PxFile
pxStandardOutput(PxArena* arena)
{
    return __pxStandardOutput__(arena);
}

PxFile
pxStandardError(PxArena* arena)
{
    return __pxStandardError__(arena);
}

PxFile
pxFileCreate(PxArena* arena, PxString8 base, PxString8 name, PxFileMode mode)
{
    return __pxFileCreate__(arena, base, name, mode);
}

PxFile
pxFileReplace(PxArena* arena, PxString8 base, PxString8 name, PxFileMode mode)
{
    return __pxFileReplace__(arena, base, name, mode);
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
pxFileDestroy(PxFile self, PxArena* arena)
{
    return __pxFileDestroy__(self, arena);
}

pxb8
pxFileDelete(PxArena* arena, PxString8 base, PxString8 name)
{
    return __pxFileDelete__(arena, base, name);
}

pxiword
pxFileWriteMemory8(PxFile self, pxu8* memory, pxiword length)
{
    return __pxFileWriteMemory8__(self, memory, length);
}

pxiword
pxFileReadMemory8(PxFile self, pxu8* memory, pxiword length)
{
    return __pxFileReadMemory8__(self, memory, length);
}

PxReader
pxReaderFromFile(PxFile self)
{
    PxReader result = {0};

    if (self == 0) return result;

    result.ctxt = self;
    result.proc = &pxFileReadMemory8;

    return result;
}

PxWriter
pxWriterFromFile(PxFile self)
{
    PxWriter result = {0};

    if (self == 0) return result;

    result.ctxt = self;
    result.proc = &pxFileWriteMemory8;

    return result;
}

#endif // PX_CORE_STORAGE_FILE_C
