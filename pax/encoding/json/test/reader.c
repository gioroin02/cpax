#include "../export.h"
#include "../../../core/memory/export.h"

#include <stdio.h>

#define COLOR_RESET "\033[0m"

#define FRONT_RED    "\033[31m"
#define FRONT_GREEN  "\033[32m"
#define FRONT_YELLOW "\033[33m"
#define FRONT_BLUE   "\033[34m"
#define FRONT_PURPLE "\033[35m"
#define FRONT_AZURE  "\033[36m"

#define RED(expr)    FRONT_RED    expr COLOR_RESET
#define GREEN(expr)  FRONT_GREEN  expr COLOR_RESET
#define YELLOW(expr) FRONT_YELLOW expr COLOR_RESET
#define BLUE(expr)   FRONT_BLUE   expr COLOR_RESET
#define PURPLE(expr) FRONT_PURPLE expr COLOR_RESET
#define AZURE(expr)  FRONT_AZURE  expr COLOR_RESET

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
    PxJsonEvent event = pxJsonReaderNext(reader, arena);

    if (event.type != PX_JSON_EVENT_OBJECT_OPEN) return;

    event = pxJsonReaderNext(reader, arena);

    while (event.type != PX_JSON_EVENT_OBJECT_CLOSE) {
        switch (event.type) {
            case PX_JSON_EVENT_STRING: {
                if (pxString8IsEqual(event.name, pxs8("name")))
                    self->name = event.value_string;
            } break;

            case PX_JSON_EVENT_UNSIGNED: {
                if (pxString8IsEqual(event.name, pxs8("code")))
                    self->code = event.value_unsigned;
            } break;

            default: break;
        }

        event = pxJsonReaderNext(reader, arena);
    }
}

int
main(int argc, char** argv)
{
    PxArena   arena  = pxMemoryReserve(16);
    PxBuffer8 source = pxBuffer8Reserve(&arena, 256);
    PxBuffer8 buffer = pxBuffer8Reserve(&arena, 256);

    Entity entity = {0};

    pxBuffer8WriteString8Tail(&source, ENTITY);

    printf(YELLOW("[start]") "\n%.*s\n" YELLOW("[stop]") "\n",
        pxCast(int, source.size), source.memory);

    printf("\n");

    PxJsonReader reader = pxJsonReaderMake(&arena, 16,
        pxBufferReader(&source, &buffer));

    jsonReadEntity(&entity, &reader, &arena);

    printf("name = %.*s, code = %llu\n", pxCast(int, entity.name.length),
        entity.name.memory, entity.code);
}
