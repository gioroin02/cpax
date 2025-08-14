#ifndef PAX_BASE_PLATFORM_H
#define PAX_BASE_PLATFORM_H

#define PAX_SIZE_NONE  0
#define PAX_SIZE_32    1
#define PAX_SIZE_64    2
#define PAX_SIZE_COUNT 3

#ifndef PAX_SIZE

    #if _WIN64 || __PL64__ || __x86_64__ || __amd64__ || __aarch64__

        #define PAX_SIZE PAX_SIZE_64

    #elif _WIN32 || __ILP32__ || _i386_

        #define PAX_SIZE PAX_SIZE_32

    #else

        #define PAX_SIZE PAX_SIZE_NONE

    #endif

#endif

#define PAX_SYSTEM_NONE    0
#define PAX_SYSTEM_WINDOWS 1
#define PAX_SYSTEM_MAX     2

#ifndef PAX_SYSTEM

    #if _WIN32

        #define PAX_SYSTEM PAX_SYSTEM_WINDOWS

    #else

        #define PAX_SYSTEM PAX_SYSTEM_NONE

    #endif

#endif

#endif // PAX_BASE_PLATFORM_H
