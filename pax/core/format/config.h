#ifndef PX_CORE_FORMAT_CONFIG_H
#define PX_CORE_FORMAT_CONFIG_H

#include "import.h"

typedef enum PxFormatFlag
{
    PX_FORMAT_FLAG_NONE         = 0x0,
    PX_FORMAT_FLAG_LEADING_ZERO = 0x1,
    PX_FORMAT_FLAG_LEADING_PLUS = 0x2,
    PX_FORMAT_FLAG_UPPER_CASE   = 0x4,
}
PxFormatFlag;

#endif // PX_CORE_FORMAT_CONFIG_H
