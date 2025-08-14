#include "../export.h"

#include <stdio.h>

int
main(int argc, char** argv)
{
    nat8 mem[12] = {0};

    mem_copy_flipped(mem, "ciao", 2, 2);

    for (Int i = 0; i < 12; i += 1)
        printf("[%-3u] ", mem[i]);
    printf("\n");

    printf("%s\n", mem);

    mem_copy_forw(mem, 4, 4, 1);

    for (Int i = 0; i < 12; i += 1)
        printf("[%-3u] ", mem[i]);
    printf("\n");

    printf("%s\n", mem);

    mem_flip(mem, 2, 2);

    for (Int i = 0; i < 12; i += 1)
        printf("[%-3u] ", mem[i]);
    printf("\n");

    printf("%s\n", mem);

    mem_copy_back(mem + 2, 2, 2, 1);

    for (Int i = 0; i < 12; i += 1)
        printf("[%-3u] ", mem[i]);
    printf("\n");

    printf("%s\n", mem);

    printf("equal = %u\n", mem_is_equal(mem, "ciao", 4, 1));
}
