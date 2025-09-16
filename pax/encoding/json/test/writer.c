#include "../export.h"

#include <stdio.h>

#define COLOR_RESET "\x1b[0m"

#define FRONT_RED "\x1b[31m"
#define FRONT_GRN "\x1b[32m"
#define FRONT_YLW "\x1b[33m"
#define FRONT_BLU "\x1b[34m"
#define FRONT_MAG "\x1b[35m"
#define FRONT_CYA "\x1b[36m"

#define RED(x) FRONT_RED x COLOR_RESET
#define GRN(x) FRONT_GRN x COLOR_RESET
#define YLW(x) FRONT_YLW x COLOR_RESET
#define BLU(x) FRONT_BLU x COLOR_RESET
#define MAG(x) FRONT_MAG x COLOR_RESET
#define CYA(x) FRONT_CYA x COLOR_RESET

typedef struct Entity
{
    PxString8 name;
    pxuword   code;
}
Entity;

void
jsonWriteEntity(Entity* self, PxJsonWriter* writer, PxArena* arena)
{
    PxJsonMsg list[] = {
        pxJsonMsgObjectOpen(),
        pxJsonMsgString(self->name, pxs8("name")),
        pxJsonMsgUnsigned(self->code, pxs8("code")),
        pxJsonMsgObjectClose(),
    };

    pxJsonWriteChain(writer, arena,
        0, pxarraylen(PxJsonMsg, list), list);
}

void
showJsonMsg(PxJsonReader* reader, PxArena* arena)
{
    PxJsonMsg message = pxJsonMsgNone();

    while (message.type != PX_JSON_MSG_COUNT) {
        message = pxJsonReadMessage(reader, arena);

        if (message.type == PX_JSON_MSG_COUNT) break;

        switch (message.type) {
            case PX_JSON_MSG_ERROR: {
                PxString8 content = message.error.content;
                PxString8 subject = message.error.subject;

                printf(RED("%.*s: %.*s"),
                    pxas(int, content.length), content.memory,
                    pxas(int, subject.length), subject.memory);

                message.type = PX_JSON_MSG_COUNT;
            } break;

            case PX_JSON_MSG_OBJECT_OPEN:
                printf("OBJECT_OPEN");
            break;

            case PX_JSON_MSG_OBJECT_CLOSE:
                printf("OBJECT_CLOSE");
            break;

            case PX_JSON_MSG_ARRAY_OPEN:
                printf("ARRAY_OPEN");
            break;

            case PX_JSON_MSG_ARRAY_CLOSE:
                printf("ARRAY_CLOSE");
            break;

            case PX_JSON_MSG_NAME:
                printf(CYA("%.*s"), pxas(int, message.name.length),
                    message.name.memory);
            break;

            case PX_JSON_MSG_STRING: {
                if (message.name.length > 0) {
                    printf(CYA("'%.*s'") ": ", pxas(int, message.name.length),
                        message.name.memory);
                }

                printf(BLU("'%.*s'"),
                    pxas(int, message.string_8.length), message.string_8.memory);
            } break;

            case PX_JSON_MSG_UNSIGNED: {
                if (message.name.length > 0) {
                    printf(CYA("'%.*s'") ": ", pxas(int, message.name.length),
                        message.name.memory);
                }

                printf(MAG("%llu"), message.unsigned_word);
            } break;

            case PX_JSON_MSG_INTEGER: {
                if (message.name.length > 0) {
                    printf(CYA("'%.*s'") ": ", pxas(int, message.name.length),
                        message.name.memory);
                }

                printf(MAG("%lli"), message.integer_word);
            } break;

            case PX_JSON_MSG_FLOATING: {
                if (message.name.length > 0) {
                    printf(CYA("'%.*s'") ": ", pxas(int, message.name.length),
                        message.name.memory);
                }

                printf(MAG("%lf"), message.floating_word);
            } break;

            case PX_JSON_MSG_BOOLEAN: {
                if (message.name.length > 0) {
                    printf(CYA("'%.*s'") ": ", pxas(int, message.name.length),
                        message.name.memory);
                }

                printf("%s", message.boolean_word != 0 ? GRN("true") : RED("false"));
            } break;

            default: break;
        }

        printf("\n");
    }
}

int
main(int argc, char** argv)
{
    PxArena   arena       = pxMemoryReserve(16);
    PxBuffer8 source      = pxBuffer8Reserve(&arena, 256);
    PxReader  buff_reader = pxBufferReader(&source, &arena, 256);
    PxWriter  buff_writer = pxBufferWriter(&source, &arena, 256);

    PxJsonWriter writer =
        pxJsonWriterMake(&arena, 16, &buff_writer);

    jsonWriteEntity(&(Entity) {.name = pxs8("gio"), .code = 156}, &writer, &arena);

    printf(YLW("[start]") "\n%.*s\n" YLW("[stop]") "\n",
        pxas(int, source.size), source.memory);

    printf("\n");

    PxJsonReader reader =
        pxJsonReaderMake(&arena, 16, &buff_reader);

    showJsonMsg(&reader, &arena);
}
