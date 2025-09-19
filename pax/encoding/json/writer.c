#ifndef PX_ENCODING_JSON_WRITER_C
#define PX_ENCODING_JSON_WRITER_C

#include "writer.h"

PxJsonWriter
pxJsonWriterReserve(PxArena* arena, pxiword length, PxWriter* writer)
{
    PxQueue stack =
        pxQueueReserve(arena, PxJsonLayerType, length);

    if (stack.length <= 0) return (PxJsonWriter) {0};

    return (PxJsonWriter) {
        .writer = writer,
        .stack  = stack,
    };
}

pxb8
pxJsonWriterNextMsg(PxJsonWriter* self, PxArena* arena, PxJsonMsg message)
{
    PxJsonLayerType parent = PX_JSON_LAYER_NONE;

    pxQueueReadTail(&self->stack, PxJsonLayerType, &parent);

    PxFmtRadix radix = PX_FORMAT_RADIX_10;
    PxFmtFlag  flags = PX_FORMAT_FLAG_NONE;

    switch (message.type) {
        case PX_JSON_MSG_OBJECT_OPEN: {
            pxWriterNextByte(self->writer, PX_ASCII_BRACE_LEFT);

            PxJsonLayerType layer = PX_JSON_LAYER_OBJECT;

            pxQueueInsertTail(&self->stack, PxJsonLayerType,
                &layer);

            self->comma = 0;
        } break;

        case PX_JSON_MSG_OBJECT_CLOSE: {
            pxWriterNextByte(self->writer,
                PX_ASCII_BRACE_RIGHT);

            pxQueueDropTail(&self->stack);

            self->comma = 1;
        } break;

        case PX_JSON_MSG_ARRAY_OPEN: {
            pxWriterNextByte(self->writer, PX_ASCII_SQUARE_LEFT);

            PxJsonLayerType layer = PX_JSON_LAYER_ARRAY;

            pxQueueInsertTail(&self->stack, PxJsonLayerType,
                &layer);

            self->comma = 0;
        } break;

        case PX_JSON_MSG_ARRAY_CLOSE: {
            pxWriterNextByte(self->writer,
                PX_ASCII_SQUARE_RIGHT);

            pxQueueDropTail(&self->stack);

            self->comma = 1;
        } break;

        case PX_JSON_MSG_NAME: {
            if (parent != PX_JSON_LAYER_OBJECT) return 0;

            if (self->comma != 0)
                pxWriterNextByte(self->writer, PX_ASCII_COMMA);

            pxWriterNextByte(self->writer, PX_ASCII_QUOTE);
            pxWriterNextString8(self->writer, message.name);
            pxWriterNextByte(self->writer, PX_ASCII_QUOTE);
            pxWriterNextByte(self->writer, PX_ASCII_COLON);
        } break;

        case PX_JSON_MSG_STRING: {
            if (self->comma != 0)
                pxWriterNextByte(self->writer, PX_ASCII_COMMA);

            if (parent == PX_JSON_LAYER_OBJECT) {
                if (message.name.length <= 0) return 0;

                pxWriterNextByte(self->writer, PX_ASCII_QUOTE);
                pxWriterNextString8(self->writer, message.name);
                pxWriterNextByte(self->writer, PX_ASCII_QUOTE);
                pxWriterNextByte(self->writer, PX_ASCII_COLON);
            }

            pxWriterNextByte(self->writer, PX_ASCII_QUOTE);
            pxWriterNextString8(self->writer, message.string_8);
            pxWriterNextByte(self->writer, PX_ASCII_QUOTE);

            self->comma = 1;
        } break;

        case PX_JSON_MSG_UNSIGNED: {
            if (self->comma != 0)
                pxWriterNextByte(self->writer, PX_ASCII_COMMA);

            if (parent == PX_JSON_LAYER_OBJECT) {
                if (message.name.length <= 0) return 0;

                pxWriterNextByte(self->writer, PX_ASCII_QUOTE);
                pxWriterNextString8(self->writer, message.name);
                pxWriterNextByte(self->writer, PX_ASCII_QUOTE);
                pxWriterNextByte(self->writer, PX_ASCII_COLON);
            }

            PxString8 string = pxString8FromUnsigned(arena,
                message.unsigned_word, radix, flags);

            pxWriterNextString8(self->writer, string);

            self->comma = 1;
        } break;

        case PX_JSON_MSG_INTEGER: {
            if (self->comma != 0)
                pxWriterNextByte(self->writer, PX_ASCII_COMMA);

            if (parent == PX_JSON_LAYER_OBJECT) {
                if (message.name.length <= 0) return 0;

                pxWriterNextByte(self->writer, PX_ASCII_QUOTE);
                pxWriterNextString8(self->writer, message.name);
                pxWriterNextByte(self->writer, PX_ASCII_QUOTE);
                pxWriterNextByte(self->writer, PX_ASCII_COLON);
            }

            PxString8 string = pxString8FromInteger(arena,
                message.integer_word, radix, flags);

            pxWriterNextString8(self->writer, string);

            self->comma = 1;
        } break;

        case PX_JSON_MSG_FLOATING: {
            return 0;
        } break;

        case PX_JSON_MSG_BOOLEAN: {
            if (self->comma != 0)
                pxWriterNextByte(self->writer, PX_ASCII_COMMA);

            if (parent == PX_JSON_LAYER_OBJECT) {
                if (message.name.length <= 0) return 0;

                pxWriterNextByte(self->writer, PX_ASCII_QUOTE);
                pxWriterNextString8(self->writer, message.name);
                pxWriterNextByte(self->writer, PX_ASCII_QUOTE);
                pxWriterNextByte(self->writer, PX_ASCII_COLON);
            }

            PxString8 string = pxString8FromBoolean(arena,
                message.boolean_word, flags);

            pxWriterNextString8(self->writer, string);

            self->comma = 1;
        } break;

        case PX_JSON_MSG_NULL: {
            if (self->comma != 0)
                pxWriterNextByte(self->writer, PX_ASCII_COMMA);

            if (parent == PX_JSON_LAYER_OBJECT) {
                if (message.name.length <= 0) return 0;

                pxWriterNextByte(self->writer, PX_ASCII_QUOTE);
                pxWriterNextString8(self->writer, message.name);
                pxWriterNextByte(self->writer, PX_ASCII_QUOTE);
                pxWriterNextByte(self->writer, PX_ASCII_COLON);
            }

            pxWriterNextString8(self->writer, pxs8("null"));

            self->comma = 1;
        } break;

        default: return 0;
    }

    pxWriterFlush(self->writer);

    return 1;
}

pxiword
pxJsonWriterNextList(PxJsonWriter* self, PxArena* arena, PxJsonMsg* values, pxiword length)
{
    for (pxiword i = 0; i < length; i += 1) {
        if (pxJsonWriterNextMsg(self, arena, values[i]) == 0)
            return i;
    }

    return length;
}

pxb8
pxJsonWriterObjectItem(PxJsonWriter* self, PxArena* arena, void* ctxt, void* proc, PxString8 name)
{
    PxJsonWriterProc* temp = pxas(PxJsonWriterProc*, proc);

    pxJsonWriterNextMsg(self, arena, pxJsonMsgName(name));

    if (proc != 0)
        return temp(ctxt, self, arena);

    return 0;
}

pxb8
pxJsonWriterObjectOpen(PxJsonWriter* self, PxArena* arena)
{
    return pxJsonWriterNextMsg(self, arena, pxJsonMsgObjectOpen());
}

pxb8
pxJsonWriterObjectClose(PxJsonWriter* self, PxArena* arena)
{
    return pxJsonWriterNextMsg(self, arena, pxJsonMsgObjectClose());
}

pxb8
pxJsonWriterArrayItem(PxJsonWriter* self, PxArena* arena, void* ctxt, void* proc)
{
    PxJsonWriterProc* temp = pxas(PxJsonWriterProc*, proc);

    if (proc != 0)
        return temp(ctxt, self, arena);

    return 0;
}

pxb8
pxJsonWriterArrayOpen(PxJsonWriter* self, PxArena* arena)
{
    return pxJsonWriterNextMsg(self, arena, pxJsonMsgArrayOpen());
}

pxb8
pxJsonWriterArrayClose(PxJsonWriter* self, PxArena* arena)
{
    return pxJsonWriterNextMsg(self, arena, pxJsonMsgArrayClose());
}

#endif // PX_ENCODING_JSON_WRITER_C
