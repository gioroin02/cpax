#ifndef PX_JSON_EVENT_H
#define PX_JSON_EVENT_H

#include "import.h"

typedef enum PxJsonLayerType
{
    PX_JSON_LAYER_NONE,
    PX_JSON_LAYER_OBJECT,
    PX_JSON_LAYER_ARRAY,
}
PxJsonLayerType;

typedef enum PxJsonEventType
{
    PX_JSON_EVENT_NONE,

    PX_JSON_EVENT_ERROR,

    PX_JSON_EVENT_OBJECT_OPEN,
    PX_JSON_EVENT_OBJECT_CLOSE,
    PX_JSON_EVENT_ARRAY_OPEN,
    PX_JSON_EVENT_ARRAY_CLOSE,

    PX_JSON_EVENT_NAME,

    PX_JSON_EVENT_STRING,
    PX_JSON_EVENT_UNSIGNED,
    PX_JSON_EVENT_INTEGER,
    PX_JSON_EVENT_FLOATING,
    PX_JSON_EVENT_BOOLEAN,
    PX_JSON_EVENT_NULL,

    PX_JSON_EVENT_COUNT,
}
PxJsonEventType;

typedef struct PxJsonEvent
{
    PxJsonEventType type;

    PxString8 string;
    PxString8 name;

    union
    {
        PxString8 error;
        pxunsig   uvalue;
        pxint     ivalue;
        pxfloat   fvalue;
        pxbool    bvalue;
    };
}
PxJsonEvent;

PxJsonEvent
pxJsonEventNone();

PxJsonEvent
pxJsonEventError(PxString8 string, PxString8 error);

PxJsonEvent
pxJsonEventObjectOpen();

PxJsonEvent
pxJsonEventObjectClose();

PxJsonEvent
pxJsonEventArrayOpen();

PxJsonEvent
pxJsonEventArrayClose();

PxJsonEvent
pxJsonEventName(PxString8 name);

PxJsonEvent
pxJsonEventString(PxString8 string, PxString8 name);

PxJsonEvent
pxJsonEventUnsigned(pxunsig value, PxString8 name);

PxJsonEvent
pxJsonEventInteger(pxint value, PxString8 name);

PxJsonEvent
pxJsonEventFloating(pxfloat value, PxString8 name);

PxJsonEvent
pxJsonEventBoolean(pxbool value, PxString8 name);

PxJsonEvent
pxJsonEventNull(PxString8 name);

PxJsonEvent
pxJsonEventCount();

#endif // PX_JSON_EVENT_H
