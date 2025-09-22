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
entityTagsWriteJson(EntityTags* self, PxJsonWriter* writer, PxArena* arena)
{
    pxJsonWriterArrayOpen(writer, arena);

    for (pxiword i = 0; i < self->size; i += 1)
        pxJsonWriterMsg(writer, arena, pxJsonMsgUnsigned(self->items[i]));

    pxJsonWriterArrayClose(writer, arena);

    return 1;
}

pxb8
entityWriteJson(Entity* self, PxJsonWriter* writer, PxArena* arena)
{
    pxJsonWriterObjectOpen(writer, arena);

    pxJsonWriterObjectItem(writer, arena,
        &self->tags, &entityTagsWriteJson, pxs8("tags"));

    pxJsonWriterList(writer, arena, (PxJsonMsg[]) {
        pxJsonMsgPair(pxs8("name"), pxJsonMsgString(self->name)),
        pxJsonMsgPair(pxs8("code"), pxJsonMsgUnsigned(self->code)),
    }, 2);

    pxJsonWriterObjectClose(writer, arena);

    return 1;
}

int
main(int argc, char** argv)
{
    PxArena   arena       = pxMemoryReserve(16);
    PxBuffer8 source      = pxBuffer8Reserve(&arena, 256);
    PxWriter  buff_writer = pxWriterFromTarget(pxTargetFromBuffer8(&source), &arena, 256);

    PxJsonWriter writer =
        pxJsonWriterReserve(&arena, 16, &buff_writer);

    entityWriteJson(&(Entity) {.name = pxs8("gio"), .code = 156, .tags = {.items = {1, 2, 3}, .size = 3}}, &writer, &arena);

    printf(YELLOW("[start]") "\n%.*s\n" YELLOW("[stop]") "\n",
        pxas(int, source.size), source.memory);
}
