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

typedef struct Entity
{
    PxString8 name;
    pxuword   code;
}
Entity;

#define ENTITY \
    pxs8("{\"name\": \"gio\", \"code\": 156}")

void
jsonReadEntity(Entity* self, PxJsonReader* reader, PxArena* arena)
{
    if (pxJsonExpectMsg(reader, arena, PX_JSON_MSG_OBJECT_OPEN) == 0)
        return;

    PxJsonMsg message = pxJsonReadMsg(reader, arena);

    while (message.type != PX_JSON_MSG_OBJECT_CLOSE) {
        switch (message.type) {
            case PX_JSON_MSG_STRING: {
                if (pxString8IsEqual(message.name, pxs8("name")))
                    self->name = message.string_8;
            } break;

            case PX_JSON_MSG_UNSIGNED: {
                if (pxString8IsEqual(message.name, pxs8("code")))
                    self->code = message.unsigned_word;
            } break;

            default: break;
        }

        message = pxJsonReadMsg(reader, arena);
    }
}

int
main(int argc, char** argv)
{
    PxArena   arena       = pxMemoryReserve(16);
    PxBuffer8 source      = pxBuffer8Reserve(&arena, 256);
    PxInput  buff_reader = pxBufferReader(&source, &arena, 256);

    Entity entity = {0};

    pxBuffer8WriteString8Tail(&source, ENTITY);

    printf(YLW("[start]") "\n%.*s\n" YLW("[stop]") "\n",
        pxas(int, source.size), source.memory);

    printf("\n");

    PxJsonReader reader =
        pxJsonReaderMake(&arena, 16, &buff_reader);

    jsonReadEntity(&entity, &reader, &arena);

    printf("name = %.*s, code = %llu\n", pxas(int, entity.name.length),
        entity.name.memory, entity.code);
}
