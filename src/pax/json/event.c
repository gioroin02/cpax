#ifndef PX_JSON_EVENT_C
#define PX_JSON_EVENT_C

#include "event.h"

PxJsonEvent
pxJsonEventNone()
{
    return (PxJsonEvent) {
        .type = PX_JSON_EVENT_NONE,
    };
}

PxJsonEvent
pxJsonEventError(PxString8 string, PxString8 error)
{
    return (PxJsonEvent) {
        .type   = PX_JSON_EVENT_ERROR,
        .string = string,
        .error  = error,
    };
}

PxJsonEvent
pxJsonEventObjectOpen()
{
    return (PxJsonEvent) {
        .type = PX_JSON_EVENT_OBJECT_OPEN,
    };
}

PxJsonEvent
pxJsonEventObjectClose()
{
    return (PxJsonEvent) {
        .type = PX_JSON_EVENT_OBJECT_CLOSE,
    };
}

PxJsonEvent
pxJsonEventArrayOpen()
{
    return (PxJsonEvent) {
        .type = PX_JSON_EVENT_ARRAY_OPEN,
    };
}

PxJsonEvent
pxJsonEventArrayClose()
{
    return (PxJsonEvent) {
        .type = PX_JSON_EVENT_ARRAY_CLOSE,
    };
}

PxJsonEvent
pxJsonEventName(PxString8 name)
{
    return (PxJsonEvent) {
        .type = PX_JSON_EVENT_NAME,
        .name = name,
    };
}

PxJsonEvent
pxJsonEventString(PxString8 string, PxString8 name)
{
    return (PxJsonEvent) {
        .type   = PX_JSON_EVENT_STRING,
        .string = string,
        .name   = name,
    };
}

PxJsonEvent
pxJsonEventUnsigned(pxunsig value, PxString8 name)
{
    return (PxJsonEvent) {
        .type   = PX_JSON_EVENT_UNSIGNED,
        .uvalue = value,
        .name   = name,
    };
}

PxJsonEvent
pxJsonEventInteger(pxint value, PxString8 name)
{
    return (PxJsonEvent) {
        .type   = PX_JSON_EVENT_INTEGER,
        .ivalue = value,
        .name   = name,
    };
}

PxJsonEvent
pxJsonEventFloating(pxfloat value, PxString8 name)
{
    return (PxJsonEvent) {
        .type   = PX_JSON_EVENT_FLOATING,
        .fvalue = value,
        .name   = name,
    };
}

PxJsonEvent
pxJsonEventBoolean(pxbool value, PxString8 name)
{
    return (PxJsonEvent) {
        .type   = PX_JSON_EVENT_BOOLEAN,
        .bvalue = value,
        .name   = name,
    };
}

PxJsonEvent
pxJsonEventNull(PxString8 name)
{
    return (PxJsonEvent) {
        .type = PX_JSON_EVENT_NULL,
        .name = name,
    };
}

PxJsonEvent
pxJsonEventCount()
{
    return (PxJsonEvent) {
        .type = PX_JSON_EVENT_COUNT,
    };
}

#endif // PX_JSON_EVENT_C
