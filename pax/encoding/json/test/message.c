#include "../export.h"
#include "../../../core/memory/export.h"

#include <stdio.h>

#define COLOR_RESET "\x1b[0m"

#define FRONT_RED    "\x1b[31m"
#define FRONT_GRN  "\x1b[32m"
#define FRONT_YLW "\x1b[33m"
#define FRONT_BLU   "\x1b[34m"
#define FRONT_MAG "\x1b[35m"
#define FRONT_CYA  "\x1b[36m"

#define RED(expr)    FRONT_RED    expr COLOR_RESET
#define GRN(expr)  FRONT_GRN  expr COLOR_RESET
#define YLW(expr) FRONT_YLW expr COLOR_RESET
#define BLU(expr)   FRONT_BLU   expr COLOR_RESET
#define MAG(expr) FRONT_MAG expr COLOR_RESET
#define CYA(expr)  FRONT_CYA  expr COLOR_RESET

#define ENTITY \
    pxs8("{ \"flags\": [16, 32], \"code\": 156, \"name\": \"player\", \"coords\": {\"x\": -1, \"y\": +2, \"z\": null}, \"alive\": true, \"pause\": false }")

void
showJsonMsg(PxJsonReader* reader, PxArena* arena)
{
    PxJsonMsg message = pxJsonMsgNone();

    while (message.type != PX_JSON_MSG_COUNT) {
        message = pxJsonReadMsg(reader, arena);

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

            case PX_JSON_MSG_NULL: {
                if (message.name.length > 0) {
                    printf(CYA("'%.*s'") ": ", pxas(int, message.name.length),
                        message.name.memory);
                }

                printf(MAG("null"));
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

    pxBuffer8WriteString8Tail(&source, ENTITY);

    printf(YLW("[start]") "\n%.*s\n" YLW("[stop]") "\n",
        pxas(int, source.size), source.memory);

    printf("\n");

    PxJsonReader reader =
        pxJsonReaderMake(&arena, 16, &buff_reader);

    showJsonMsg(&reader, &arena);
}
