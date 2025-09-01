#ifndef PX_STRING_LIST_C
#define PX_STRING_LIST_C

#include "list.h"

PxStringList
pxStringListFromString8(PxArena* arena, PxString8 string, PxString8 pivot)
{
    PxStringList result = {0};

    pxStringListInsertString8Tail(&result, arena, string, pivot);

    return result;
}

PxStringList
pxStringListFromString16(PxArena* arena, PxString16 string, PxString16 pivot)
{
    PxStringList result = {0};

    pxStringListInsertString16Tail(&result, arena, string, pivot);

    return result;
}

PxStringList
pxStringListFromString32(PxArena* arena, PxString32 string, PxString32 pivot)
{
    PxStringList result = {0};

    pxStringListInsertString32Tail(&result, arena, string, pivot);

    return result;
}

pxb8
pxStringListInsertNodeHead(PxStringList* self, PxStringListNode* value)
{
    if (value == 0) return 0;

    if (value->memory == 0 || value->length <= 0)
        return 0;

    if (self->tail == 0)
        self->tail = value;

    if (self->head != 0)
        value->next = self->head;

    self->head  = value;
    self->size += 1;

    return 1;
}

pxb8
pxStringListInsertString8Head(PxStringList* self, PxArena* arena, PxString8 value, PxString8 pivot)
{
    pxiword offset = pxArenaOffset(arena);

    PxString8 left  = {0};
    PxString8 right = value;

    while (right.length > 0) {
        pxString8Split(right, pivot, &left, &right);

        if (left.length > 0) {
            PxString32 string = pxString32CopyString8(arena, left);

            if (string.memory == 0 || string.length <= 0)
                break;

            PxStringListNode* node = pxArenaReserve(arena, PxStringListNode, 1);

            if (node == 0) break;

            node->memory = string.memory;
            node->length = string.length;

            if (pxStringListInsertNodeHead(self, node) == 0) break;
        }
    }

    if (right.length <= 0) return 1;

    pxArenaRewind(arena, offset);

    return 0;
}

pxb8
pxStringListInsertString16Head(PxStringList* self, PxArena* arena, PxString16 value, PxString16 pivot)
{
    pxiword offset = pxArenaOffset(arena);

    PxString16 left  = {0};
    PxString16 right = value;

    while (right.length > 0) {
        pxString16Split(right, pivot, &left, &right);

        if (left.length > 0) {
            PxString32 string = pxString32CopyString16(arena, left);

            if (string.memory == 0 || string.length <= 0)
                break;

            PxStringListNode* node = pxArenaReserve(arena, PxStringListNode, 1);

            if (node == 0) break;

            node->memory = string.memory;
            node->length = string.length;

            if (pxStringListInsertNodeHead(self, node) == 0) break;
        }
    }

    if (right.length <= 0) return 1;

    pxArenaRewind(arena, offset);

    return 0;
}

pxb8
pxStringListInsertString32Head(PxStringList* self, PxArena* arena, PxString32 value, PxString32 pivot)
{
    pxiword offset = pxArenaOffset(arena);

    PxString32 left  = {0};
    PxString32 right = value;

    while (right.length > 0) {
        pxString32Split(right, pivot, &left, &right);

        if (left.length > 0) {
            PxString32 string = pxString32Copy(arena, left);

            if (string.memory == 0 || string.length <= 0)
                break;

            PxStringListNode* node = pxArenaReserve(arena, PxStringListNode, 1);

            if (node == 0) break;

            node->memory = string.memory;
            node->length = string.length;

            if (pxStringListInsertNodeHead(self, node) == 0) break;
        }
    }

    if (right.length <= 0) return 1;

    pxArenaRewind(arena, offset);

    return 0;
}

pxb8
pxStringListInsertNodeTail(PxStringList* self, PxStringListNode* value)
{
    if (value == 0) return 0;

    if (value->memory == 0 || value->length <= 0)
        return 0;

    if (self->head == 0)
        self->head = value;

    if (self->tail != 0)
        self->tail->next = value;

    self->tail  = value;
    self->size += 1;

    return 1;
}

pxb8
pxStringListInsertString8Tail(PxStringList* self, PxArena* arena, PxString8 value, PxString8 pivot)
{
    pxiword offset = pxArenaOffset(arena);

    PxString8 left  = {0};
    PxString8 right = value;

    while (right.length > 0) {
        pxString8Split(right, pivot, &left, &right);

        if (left.length > 0) {
            PxString32 string = pxString32CopyString8(arena, left);

            if (string.memory == 0 || string.length <= 0)
                break;

            PxStringListNode* node = pxArenaReserve(arena, PxStringListNode, 1);

            if (node == 0) break;

            node->memory = string.memory;
            node->length = string.length;

            if (pxStringListInsertNodeTail(self, node) == 0) break;
        }
    }

    if (right.length <= 0) return 1;

    pxArenaRewind(arena, offset);

    return 0;
}

pxb8
pxStringListInsertString16Tail(PxStringList* self, PxArena* arena, PxString16 value, PxString16 pivot)
{
    pxiword offset = pxArenaOffset(arena);

    PxString16 left  = {0};
    PxString16 right = value;

    while (right.length > 0) {
        pxString16Split(right, pivot, &left, &right);

        if (left.length > 0) {
            PxString32 string = pxString32CopyString16(arena, left);

            if (string.memory == 0 || string.length <= 0)
                break;

            PxStringListNode* node = pxArenaReserve(arena, PxStringListNode, 1);

            if (node == 0) break;

            node->memory = string.memory;
            node->length = string.length;

            if (pxStringListInsertNodeTail(self, node) == 0) break;
        }
    }

    if (right.length <= 0) return 1;

    pxArenaRewind(arena, offset);

    return 0;
}

pxb8
pxStringListInsertString32Tail(PxStringList* self, PxArena* arena, PxString32 value, PxString32 pivot)
{
    pxiword offset = pxArenaOffset(arena);

    PxString32 left  = {0};
    PxString32 right = value;

    while (right.length > 0) {
        pxString32Split(right, pivot, &left, &right);

        if (left.length > 0) {
            PxString32 string = pxString32Copy(arena, left);

            if (string.memory == 0 || string.length <= 0)
                break;

            PxStringListNode* node = pxArenaReserve(arena, PxStringListNode, 1);

            if (node == 0) break;

            node->memory = string.memory;
            node->length = string.length;

            if (pxStringListInsertNodeTail(self, node) == 0) break;
        }
    }

    if (right.length <= 0) return 1;

    pxArenaRewind(arena, offset);

    return 0;
}

PxString8
pxString8FromStringList(PxArena* arena, PxStringList* value, PxString8 pivot)
{
    pxiword length = 0;

    for (PxStringListNode* node = value->head; node != 0; node = node->next) {
        length += pxUtf8UnitsFromMemory32(
            node->memory, node->length);

        if (node->next != 0)
            length += pivot.length;
    }

    pxu8* result = pxArenaReserve(arena, pxu8, length + 1);

    if (result == 0) return (PxString8) {0};

    pxiword offset = pxArenaOffset(arena);
    pxiword index  = 0;

    for (PxStringListNode* node = value->head; node != 0; node = node->next) {
        PxString8 string = pxString8CopyString32(arena,
            (PxString32) {.memory = node->memory, .length = node->length});

        for (pxiword i = 0; i < string.length; i += 1)
            result[index + i] = string.memory[i];

        index += string.length;

        if (node->next != 0) {
            for (pxiword i = 0; i < pivot.length; i += 1)
                result[index + i] = pivot.memory[i];

            index += pivot.length;
        }
    }

    return (PxString8) {
        .memory = result,
        .length = length,
    };
}

PxString16
pxString16FromStringList(PxArena* arena, PxStringList* value, PxString16 pivot)
{
    pxiword length = 0;

    for (PxStringListNode* node = value->head; node != 0; node = node->next) {
        length += pxUtf16UnitsFromMemory32(
            node->memory, node->length);

        if (node->next != 0)
            length += pivot.length;
    }

    pxu16* result = pxArenaReserve(arena, pxu16, length + 1);

    if (result == 0) return (PxString16) {0};

    pxiword offset = pxArenaOffset(arena);
    pxiword index  = 0;

    for (PxStringListNode* node = value->head; node != 0; node = node->next) {
        PxString16 string = pxString16CopyString32(arena,
            (PxString32) {.memory = node->memory, .length = node->length});

        for (pxiword i = 0; i < string.length; i += 1)
            result[index + i] = string.memory[i];

        index += string.length;

        if (node->next != 0) {
            for (pxiword i = 0; i < pivot.length; i += 1)
                result[index + i] = pivot.memory[i];

            index += pivot.length;
        }
    }

    return (PxString16) {
        .memory = result,
        .length = length,
    };
}

PxString32
pxString32FromStringList(PxArena* arena, PxStringList* value, PxString32 pivot)
{
    pxiword length = 0;

    for (PxStringListNode* node = value->head; node != 0; node = node->next) {
        length += node->length;

        if (node->next != 0)
            length += pivot.length;
    }

    pxu32* result = pxArenaReserve(arena, pxu32, length + 1);

    if (result == 0) return (PxString32) {0};

    pxiword offset = pxArenaOffset(arena);
    pxiword index  = 0;

    for (PxStringListNode* node = value->head; node != 0; node = node->next) {
        PxString32 string = {.memory = node->memory, .length = node->length};

        for (pxiword i = 0; i < string.length; i += 1)
            result[index + i] = string.memory[i];

        index += string.length;

        if (node->next != 0) {
            for (pxiword i = 0; i < pivot.length; i += 1)
                result[index + i] = pivot.memory[i];

            index += pivot.length;
        }
    }

    return (PxString32) {
        .memory = result,
        .length = length,
    };
}

#endif // PX_STRING_LIST_C
