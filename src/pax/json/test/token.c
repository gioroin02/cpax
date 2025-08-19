#include "../export.h"
#include "../../memory/export.h"

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

static const PxString8 ENTITY = pxStr8(
    "{ \"flags\": [16, 32], \"code\": 156, \"name\": \"player\", \"coords\": {\"x\": 1, \"y\": 2} }"
);

static const char* const JSON_TOKEN_NAMES[] = {
    pxString(JSON_TOKEN_NONE),
    pxString(JSON_TOKEN_ERROR),
    pxString(JSON_TOKEN_OBJECT_OPEN),
    pxString(JSON_TOKEN_OBJECT_CLOSE),
    pxString(JSON_TOKEN_ARRAY_OPEN),
    pxString(JSON_TOKEN_ARRAY_CLOSE),
    pxString(JSON_TOKEN_COLON),
    pxString(JSON_TOKEN_COMMA),
    pxString(JSON_TOKEN_STRING),
    pxString(JSON_TOKEN_UNSIGNED),
    pxString(JSON_TOKEN_INTEGER),
    pxString(JSON_TOKEN_FLOATING),
    pxString(JSON_TOKEN_BOOLEAN),
    pxString(JSON_TOKEN_NULL),
    pxString(JSON_TOKEN_COUNT),
};

void
showJsonToken(PxReader* reader, PxArena* arena)
{
    PxJsonToken token = pxJsonTokenNone();

    while (token.type != PX_JSON_TOKEN_COUNT) {
        token = pxJsonNext(reader, arena);

        switch (token.type) {
            case PX_JSON_TOKEN_ERROR:
                printf(RED("%.*s"), pxCast(int, token.error.length),
                    token.error.memory);

                token.type = PX_JSON_TOKEN_COUNT;
            break;

            case PX_JSON_TOKEN_STRING:
                printf(BLUE("'%.*s'"), pxCast(int, token.string.length),
                    token.string.memory);
            break;

            case PX_JSON_TOKEN_UNSIGNED:
                printf(PURPLE("%llu"), token.uvalue);
            break;

            case PX_JSON_TOKEN_INTEGER:
                printf(PURPLE("%lli"), token.ivalue);
            break;

            case PX_JSON_TOKEN_FLOATING:
                printf(PURPLE("%lf"), token.fvalue);
            break;

            case PX_JSON_TOKEN_BOOLEAN:
                printf("%s", token.bvalue != 0 ? GREEN("true") : RED("false"));
            break;

            case PX_JSON_TOKEN_COUNT: break;

            default:
                printf("%.*s", pxCast(int, token.string.length),
                    token.string.memory);
            break;
        }

        printf("\n");
    }
}

int
main(int argc, char** argv)
{
    PxArena   arena  = pxMemoryReserve(16);
    PxBuffer8 source = pxBuffer8Reserve(&arena, 256);
    PxBuffer8 buffer = pxBuffer8Reserve(&arena, 256);

    pxBuffer8WriteStringTail(&source, ENTITY);

    printf(YELLOW("[start]") "\n%.*s\n" YELLOW("[stop]") "\n",
        pxCast(int, source.size), source.memory);

    printf("\n");

    PxReader reader = pxBufferReader(&source, &buffer);

    showJsonToken(&reader, &arena);
}
