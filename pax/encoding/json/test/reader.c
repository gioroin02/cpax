#include "../export.h"
#include "../../../core/memory/export.h"

#include <stdio.h>

#define COLOR_RESET "\x1b[0m"

#define FRONT_RED    "\x1b[31m"
#define FRONT_GREEN  "\x1b[32m"
#define FRONT_YELLOW "\x1b[33m"
#define FRONT_BLUE   "\x1b[34m"
#define FRONT_PURPLE "\x1b[35m"
#define FRONT_AZURE  "\x1b[36m"

#define RED(expr)    FRONT_RED    expr COLOR_RESET
#define GREEN(expr)  FRONT_GREEN  expr COLOR_RESET
#define YELLOW(expr) FRONT_YELLOW expr COLOR_RESET
#define BLUE(expr)   FRONT_BLUE   expr COLOR_RESET
#define PURPLE(expr) FRONT_PURPLE expr COLOR_RESET
#define AZURE(expr)  FRONT_AZURE  expr COLOR_RESET

typedef pxiword EntityTag;

#define ENTITY_TAGS_ITEMS pxas(pxiword, 16)

typedef struct EntityTags
{
    EntityTag items[ENTITY_TAGS_ITEMS];
    pxiword   size;
}
EntityTags;

typedef struct Entity
{
    PxString8 name;
    pxuword   code;

    EntityTags tags;
}
Entity;

#define ENTITY \
    pxs8("{\"name\": \"gio\", \"code\": 156, \"tags\": [1, -2, true, null, false, \"something\"]}")

pxb8
entityTagsReadJson(EntityTags* self, PxJsonReader* reader, PxArena* arena)
{
    PxJsonMsg message = {0};

    if (pxJsonReaderArrayOpen(reader, arena, &message) == 0) return 0;

    while (pxJsonReaderArrayClose(reader, arena, &message) == 0) {
        if (self->size < 0 || self->size >= ENTITY_TAGS_ITEMS)
            continue;

        switch (message.type) {
            case PX_JSON_MSG_STRING: {
                if (message.string_8.length > 0)
                    self->items[self->size] = message.string_8.memory[0];
            } break;

            case PX_JSON_MSG_UNSIGNED: {
                self->items[self->size] = message.unsigned_word;
            } break;

            case PX_JSON_MSG_INTEGER: {
                self->items[self->size] = message.integer_word;
            } break;

            case PX_JSON_MSG_BOOLEAN: {
                self->items[self->size] = message.boolean_word;
            } break;

            default: break;
        }

        self->size += 1;
    }

    return 1;
}

pxb8
entityReadJson(Entity* self, PxJsonReader* reader, PxArena* arena)
{
    PxJsonMsg message = {0};

    if (pxJsonReaderObjectOpen(reader, arena, &message) == 0) return 0;

    while (pxJsonReaderObjectClose(reader, arena, &message) == 0) {
        switch (message.type) {
            case PX_JSON_MSG_NAME: {
                if (pxString8IsEqual(message.name, pxs8("tags")) != 0)
                    entityTagsReadJson(&self->tags, reader, arena);
            } break;

            case PX_JSON_MSG_STRING: {
                if (pxString8IsEqual(message.name, pxs8("name")) != 0)
                    self->name = message.string_8;
            } break;

            case PX_JSON_MSG_UNSIGNED: {
                if (pxString8IsEqual(message.name, pxs8("code")) != 0)
                    self->code = message.unsigned_word;
            } break;

            default: break;
        }
    }

    return 1;
}

int
main(int argc, char** argv)
{
    PxArena   arena       = pxMemoryReserve(16);
    PxBuffer8 source      = pxBuffer8Reserve(&arena, 256);
    PxReader  buff_reader = pxReaderFromInput(pxInputFromBuffer8(&source), &arena, 256);

    Entity entity = {0};

    pxBuffer8WriteString8Tail(&source, ENTITY);

    printf(YELLOW("[start]") "\n%.*s\n" YELLOW("[stop]") "\n",
        pxas(int, source.size), source.memory);

    printf("\n");

    PxJsonReader reader =
        pxJsonReaderReserve(&arena, 16, &buff_reader);

    entityReadJson(&entity, &reader, &arena);

    printf("name = %.*s\n",
        pxas(int, entity.name.length), entity.name.memory);

    printf("code = %llu\n", entity.code);

    for (pxiword i = 0; i < entity.tags.size; i += 1)
        printf("tag  = %lli\n", entity.tags.items[i]);
}
