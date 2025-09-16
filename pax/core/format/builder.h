#ifndef PX_CORE_FORMAT_BUILDER_H
#define PX_CORE_FORMAT_BUILDER_H

#include "unsigned.h"
#include "integer.h"

typedef enum PxFormatItemType
{
    PX_FORMAT_ITEM_NONE,

    PX_FORMAT_ITEM_STRING_8,
    PX_FORMAT_ITEM_STRING_16,
    PX_FORMAT_ITEM_STRING_32,

    PX_FORMAT_ITEM_UNICODE,

    PX_FORMAT_ITEM_UNSIGNED,
    PX_FORMAT_ITEM_INTEGER,
    PX_FORMAT_ITEM_FLOATING,
    PX_FORMAT_ITEM_BOOLEAN,

    PX_FORMAT_ITEM_DELEGATE,
}
PxFormatItemType;

typedef struct PxFormatItemUnsigned
{
    PxFormatRadix radix;
    PxFormatFlag  flags;
    pxuword       value;
}
PxFormatItemUnsigned;

typedef struct PxFormatItemInteger
{
    PxFormatRadix radix;
    PxFormatFlag  flags;
    pxiword       value;
}
PxFormatItemInteger;

typedef struct PxFormatItemFloating
{
    PxFormatRadix radix;
    PxFormatFlag  flags;
    pxfword       value;
}
PxFormatItemFloating;

typedef struct PxFormatItemBoolean
{
    PxFormatFlag flags;
    pxbword      value;
}
PxFormatItemBoolean;

typedef struct PxFormatItemDelegate
{
    void* ctxt;
    void* proc;
}
PxFormatItemDelegate;

typedef struct PxFormatItem
{
    PxFormatItemType type;

    union
    {
        PxString8  string_8;
        PxString16 string_16;
        PxString32 string_32;

        pxi32 unicode;

        PxFormatItemUnsigned unsigned_word;
        PxFormatItemInteger  integer_word;
        PxFormatItemFloating floating_word;
        PxFormatItemBoolean  boolean_word;

        PxFormatItemDelegate delegate;
    };
}
PxFormatItem;

typedef struct PxBuilder
{

}
PxBuilder;

#endif // PX_CORE_FORMAT_BUILDER_H
