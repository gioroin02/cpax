#ifndef PX_JSON_READER_C
#define PX_JSON_READER_C

#include "reader.h"

PxJsonReader
pxJsonReaderMake(PxArena* arena, pxint length, PxReader reader)
{
    PxQueue stack =
        pxQueueReserve(arena, PxJsonLayerType, length);

    if (stack.length <= 0) return (PxJsonReader) {0};

    return (PxJsonReader) {
        .reader = reader,
        .stack  = stack,
    };
}

PxJsonEvent
pxJsonReaderNext(PxJsonReader* self, PxArena* arena)
{
    PxJsonEvent     result = pxJsonEventCount();
    PxJsonLayerType parent = PX_JSON_LAYER_NONE;

    while (result.type == PX_JSON_EVENT_COUNT) {
        if (pxQueueReadTail(&self->stack, PxJsonLayerType, &parent) == 0)
            parent = PX_JSON_LAYER_NONE;

        PxJsonToken token = pxJsonNext(&self->reader, arena);

        if (token.type == PX_JSON_TOKEN_COUNT) break;

        switch (token.type) {
            case PX_JSON_TOKEN_ERROR: {
                result = pxJsonEventError(token.string, token.error);
            } break;

            case PX_JSON_TOKEN_OBJECT_OPEN: {
                result = pxJsonEventObjectOpen(token.string);

                PxJsonLayerType layer = PX_JSON_LAYER_OBJECT;

                pxQueueInsertTail(&self->stack, PxJsonLayerType,
                    &layer);

                self->name  = (PxString8) {0};
                self->colon = 0;
                self->comma = 0;
                } break;

            case PX_JSON_TOKEN_OBJECT_CLOSE: {
                result = pxJsonEventObjectClose(token.string);

                pxQueueDropTail(&self->stack);

                if (pxQueueReadTail(&self->stack, PxJsonLayerType, &parent) == 0)
                    parent = PX_JSON_LAYER_NONE;

                self->name  = (PxString8) {0};
                self->colon = 0;
                self->comma = 0;
            } break;

            case PX_JSON_TOKEN_ARRAY_OPEN: {
                result = pxJsonEventArrayOpen(token.string);

                PxJsonLayerType layer = PX_JSON_LAYER_ARRAY;

                pxQueueInsertTail(&self->stack, PxJsonLayerType,
                    &layer);

                self->name  = (PxString8) {0};
                self->colon = 0;
                self->comma = 0;
            } break;

            case PX_JSON_TOKEN_ARRAY_CLOSE: {
                result = pxJsonEventArrayClose(token.string);

                pxQueueDropTail(&self->stack);

                if (pxQueueReadTail(&self->stack, PxJsonLayerType, &parent) == 0)
                    parent = PX_JSON_LAYER_NONE;

                self->name  = (PxString8) {0};
                self->colon = 0;
                self->comma = 0;
            } break;

            case PX_JSON_TOKEN_COLON: {
                if (parent == PX_JSON_LAYER_OBJECT) {
                    token = pxJsonPeek(&self->reader, arena);

                    switch (token.type) {
                        case PX_JSON_TOKEN_OBJECT_OPEN:
                        case PX_JSON_TOKEN_ARRAY_OPEN:
                            result = pxJsonEventName();
                        break;

                        default: break;
                    }
                }

                self->colon = 1;
                self->comma = 0;
            } break;

            case PX_JSON_TOKEN_COMMA: {
                self->name  = (PxString8) {0};
                self->colon = 0;
                self->comma = 1;
            } break;

            case PX_JSON_TOKEN_STRING: {
                if (parent != PX_JSON_LAYER_OBJECT || self->colon != 0)
                    result = pxJsonEventString(token.string);
                else
                    self->name = token.string;

                self->colon = 0;
                self->comma = 0;
            } break;

            case PX_JSON_TOKEN_UNSIGNED: {
                result =
                    pxJsonEventUnsigned(token.string, token.uvalue);

                self->colon = 0;
                self->comma = 0;
            } break;

            case PX_JSON_TOKEN_INTEGER: {
                result =
                    pxJsonEventInteger(token.string, token.ivalue);

                self->colon = 0;
                self->comma = 0;
            } break;

            case PX_JSON_TOKEN_FLOATING: {
                result =
                    pxJsonEventFloating(token.string, token.fvalue);

                self->colon = 0;
                self->comma = 0;
            } break;

            case PX_JSON_TOKEN_BOOLEAN: {
                result =
                    pxJsonEventBoolean(token.string, token.bvalue);

                self->colon = 0;
                self->comma = 0;
            } break;

            case PX_JSON_TOKEN_NULL: {
                result = pxJsonEventNull(token.string);

                self->colon = 0;
                self->comma = 0;
            } break;

            default: break;
        }
    }

    switch (parent) {
        case PX_JSON_LAYER_OBJECT:
            result = pxJsonEventObject(result, self->name);
        break;

        case PX_JSON_LAYER_ARRAY:
            result = pxJsonEventArray(result);
        break;

        default: break;
    }

    return result;
}

#endif // PX_JSON_READER_C
