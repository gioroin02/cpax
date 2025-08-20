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
pxJsonEventObjectOpen(PxString8 string)
{
    return (PxJsonEvent) {
        .type   = PX_JSON_EVENT_OBJECT_OPEN,
        .string = string,
    };
}

PxJsonEvent
pxJsonEventObjectClose(PxString8 string)
{
    return (PxJsonEvent) {
        .type   = PX_JSON_EVENT_OBJECT_CLOSE,
        .string = string,
    };
}

PxJsonEvent
pxJsonEventArrayOpen(PxString8 string)
{
    return (PxJsonEvent) {
        .type   = PX_JSON_EVENT_ARRAY_OPEN,
        .string = string,
    };
}

PxJsonEvent
pxJsonEventArrayClose(PxString8 string)
{
    return (PxJsonEvent) {
        .type   = PX_JSON_EVENT_ARRAY_CLOSE,
        .string = string,
    };
}

PxJsonEvent
pxJsonEventName()
{
    return (PxJsonEvent) {
        .type = PX_JSON_EVENT_NAME,
    };
}

PxJsonEvent
pxJsonEventString(PxString8 string)
{
    return (PxJsonEvent) {
        .type   = PX_JSON_EVENT_STRING,
        .string = string,
    };
}

PxJsonEvent
pxJsonEventUnsigned(PxString8 string, pxunsig value)
{
    return (PxJsonEvent) {
        .type   = PX_JSON_EVENT_UNSIGNED,
        .string = string,
        .uvalue = value,
    };
}

PxJsonEvent
pxJsonEventInteger(PxString8 string, pxint value)
{
    return (PxJsonEvent) {
        .type   = PX_JSON_EVENT_INTEGER,
        .string = string,
        .ivalue = value,
    };
}

PxJsonEvent
pxJsonEventFloating(PxString8 string, pxfloat value)
{
    return (PxJsonEvent) {
        .type   = PX_JSON_EVENT_FLOATING,
        .string = string,
        .fvalue = value,
    };
}

PxJsonEvent
pxJsonEventBoolean(PxString8 string, pxbool value)
{
    return (PxJsonEvent) {
        .type   = PX_JSON_EVENT_BOOLEAN,
        .string = string,
        .bvalue = value,
    };
}

PxJsonEvent
pxJsonEventNull(PxString8 string)
{
    return (PxJsonEvent) {
        .type   = PX_JSON_EVENT_NULL,
        .string = string,
    };
}

PxJsonEvent
pxJsonEventCount()
{
    return (PxJsonEvent) {
        .type = PX_JSON_EVENT_COUNT,
    };
}

PxJsonEvent
pxJsonEventObject(PxJsonEvent value, PxString8 name)
{
    value.parent = PX_JSON_LAYER_OBJECT;
    value.name   = name;

    return value;
}

PxJsonEvent
pxJsonEventArray(PxJsonEvent value)
{
    value.parent = PX_JSON_LAYER_ARRAY;

    return value;
}

#endif // PX_JSON_EVENT_C
