#include "../export.h"

#include <stdio.h>

int
main(int argc, char** argv)
{
    PxArena arena = pxMemoryReserve(16);

    PxConsoleQueue queue =
        pxConsoleQueueReserve(&arena, PX_MEMORY_KIB);

    pxConsoleQueueWriteList(&queue, &arena, (PxConsoleMsg[]) {
        pxConsoleMsgCursorMoveRight(1),
        pxConsoleMsgStyleText256(55),
    }, 2);

    for (pxiword i = 0; i < queue.buffer.size; i += 1) {
        pxu8 byte = pxBuffer8GetForwOr(&queue.buffer, i, 0);

        if (byte > 0x20 && byte < 0x80)
            printf("%c", byte);
        else
            printf("\\x%02x", byte);
    }

    printf("\n");

    PxConsoleMsg value = pxConsoleQueueReadMsg(&queue, &arena);

    for (pxiword i = 0; i < queue.buffer.size; i += 1) {
        pxu8 byte = pxBuffer8GetForwOr(&queue.buffer, i, 0);

        if (byte > 0x20 && byte < 0x80)
            printf("%c", byte);
        else
            printf("\\x%02x", byte);
    }

    printf("\n");
}
