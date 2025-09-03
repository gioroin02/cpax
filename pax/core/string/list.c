#ifndef PX_STRING_LIST_C
#define PX_STRING_LIST_C

#include "list.h"

PxStringList
pxStringListFromString8(PxArena* arena, PxString8 string, PxString8 pivot)
{
    PxStringList result = {0};

    pxStringListInsertString8(&result, arena, string, pivot);

    return result;
}

PxStringList
pxStringListFromString16(PxArena* arena, PxString16 string, PxString16 pivot)
{
    PxStringList result = {0};

    pxStringListInsertString16(&result, arena, string, pivot);

    return result;
}

PxStringList
pxStringListFromString32(PxArena* arena, PxString32 string, PxString32 pivot)
{
    PxStringList result = {0};

    pxStringListInsertString32(&result, arena, string, pivot);

    return result;
}

pxb8
pxStringListInsertNode(PxStringList* self, PxStringNode* value)
{
    if (value == 0) return 0;

    PxStringNode* tail = self->tail;

    if (self->head == 0) self->head = value;

    if (self->tail != 0) {
        value->prev = tail;
        tail->next  = value;
    }

    self->tail  = value;
    self->size += 1;

    return 1;
}

PxStringNode*
pxStringListRemoveNode(PxStringList* self)
{
    if (self->size <= 0) return 0;

    PxStringNode* result = self->tail;

    if (self->head == self->tail)
        self->head = 0;

    PxStringNode* tail = self->tail->prev;

    self->tail  = tail;
    self->size -= 1;

    if (tail != 0) tail->next = 0;

    result->next = 0;
    result->prev = 0;

    return result;
}

pxb8
pxStringListInsertString8(PxStringList* self, PxArena* arena, PxString8 value, PxString8 pivot)
{
    pxiword offset = pxArenaOffset(arena);

    PxString8 left  = {0};
    PxString8 right = value;

    while (right.length > 0) {
        pxString8Split(right, pivot, &left, &right);

        PxString8 string = pxString8Copy(arena, left);

        PxStringNode* node =
            pxArenaReserve(arena, PxStringNode, 1);

        if (string.length != left.length || node == 0)
            break;

        node->memory = string.memory;
        node->length = string.length;

        pxStringListInsertNode(self, node);
    }

    if (right.length <= 0) return 1;

    pxArenaRewind(arena, offset);

    return 0;
}

pxb8
pxStringListInsertString16(PxStringList* self, PxArena* arena, PxString16 value, PxString16 pivot)
{
    pxiword offset = pxArenaOffset(arena);

    PxString16 left  = {0};
    PxString16 right = value;

    while (right.length > 0) {
        pxString16Split(right, pivot, &left, &right);

        PxString8 string = pxString8CopyString16(arena, left);

        PxStringNode* node =
            pxArenaReserve(arena, PxStringNode, 1);

        if (string.length != left.length || node == 0)
            break;

        node->memory = string.memory;
        node->length = string.length;

        pxStringListInsertNode(self, node);
    }

    if (right.length <= 0) return 1;

    pxArenaRewind(arena, offset);

    return 0;
}

pxb8
pxStringListInsertString32(PxStringList* self, PxArena* arena, PxString32 value, PxString32 pivot)
{
    pxiword offset = pxArenaOffset(arena);

    PxString32 left  = {0};
    PxString32 right = value;

    while (right.length > 0) {
        pxString32Split(right, pivot, &left, &right);

        PxString8 string = pxString8CopyString32(arena, left);

        PxStringNode* node =
            pxArenaReserve(arena, PxStringNode, 1);

        if (string.length != left.length || node == 0)
            break;

        node->memory = string.memory;
        node->length = string.length;

        pxStringListInsertNode(self, node);
    }

    if (right.length <= 0) return 1;

    pxArenaRewind(arena, offset);

    return 0;
}

PxString8
pxString8FromStringList(PxArena* arena, PxStringList* value, PxString8 pivot, PxString8 prefix, PxString8 suffix)
{
    pxiword length = prefix.length + suffix.length;

    for (PxStringNode* node = value->head; node != 0; node = node->next) {
        length += node->length;

        if (node->next != 0)
            length += pivot.length;
    }

    pxu8* result = pxArenaReserve(arena, pxu8, length + 1);

    if (result == 0) return (PxString8) {0};

    pxiword offset = pxArenaOffset(arena);
    pxiword index  = 0;

    for (pxiword i = 0; i < prefix.length; i += 1)
        result[index + i] = prefix.memory[i];

    index += prefix.length;

    for (PxStringNode* node = value->head; node != 0; node = node->next) {
        PxString8 string = {.memory = node->memory, .length = node->length};

        for (pxiword i = 0; i < string.length; i += 1)
            result[index + i] = string.memory[i];

        index += string.length;

        if (node->next != 0) {
            for (pxiword i = 0; i < pivot.length; i += 1)
                result[index + i] = pivot.memory[i];

            index += pivot.length;
        }
    }

    for (pxiword i = 0; i < suffix.length; i += 1)
        result[index + i] = suffix.memory[i];

    index += suffix.length;

    return (PxString8) {
        .memory = result,
        .length = length,
    };
}

PxString16
pxString16FromStringList(PxArena* arena, PxStringList* value, PxString16 pivot, PxString16 prefix, PxString16 suffix)
{
    pxiword length = prefix.length + suffix.length;

    for (PxStringNode* node = value->head; node != 0; node = node->next) {
        length += pxUtf16UnitsFromMemory8(
            node->memory, node->length);

        if (node->next != 0)
            length += pivot.length;
    }

    pxu16* result = pxArenaReserve(arena, pxu16, length + 1);

    if (result == 0) return (PxString16) {0};

    pxiword offset = pxArenaOffset(arena);
    pxiword index  = 0;

    for (pxiword i = 0; i < prefix.length; i += 1)
        result[index + i] = prefix.memory[i];

    index += prefix.length;

    for (PxStringNode* node = value->head; node != 0; node = node->next) {
        pxiword other = 0;

        while (other < node->length) {
            pxi32 unicode = 0;

            other += pxUtf8ReadMemory8Forw(
                node->memory, node->length, other, &unicode);

            index += pxUtf16WriteMemory16Forw(
                result, length, index, unicode);
        }

        if (node->next != 0) {
            for (pxiword i = 0; i < pivot.length; i += 1)
                result[index + i] = pivot.memory[i];

            index += pivot.length;
        }
    }

    for (pxiword i = 0; i < suffix.length; i += 1)
        result[index + i] = suffix.memory[i];

    index += suffix.length;

    return (PxString16) {
        .memory = result,
        .length = length,
    };
}

PxString32
pxString32FromStringList(PxArena* arena, PxStringList* value, PxString32 pivot, PxString32 prefix, PxString32 suffix)
{
    pxiword length = prefix.length + suffix.length;

    for (PxStringNode* node = value->head; node != 0; node = node->next) {
        length += pxUtf32UnitsFromMemory8(
            node->memory, node->length);

        if (node->next != 0)
            length += pivot.length;
    }

    pxu32* result = pxArenaReserve(arena, pxu32, length + 1);

    if (result == 0) return (PxString32) {0};

    pxiword offset = pxArenaOffset(arena);
    pxiword index  = 0;

    for (pxiword i = 0; i < prefix.length; i += 1)
        result[index + i] = prefix.memory[i];

    index += prefix.length;

    for (PxStringNode* node = value->head; node != 0; node = node->next) {
        pxiword other = 0;

        while (other < node->length) {
            pxi32 unicode = 0;

            other += pxUtf8ReadMemory8Forw(
                node->memory, node->length, other, &unicode);

            index += pxUtf32WriteMemory32Forw(
                result, length, index, unicode);
        }

        if (node->next != 0) {
            for (pxiword i = 0; i < pivot.length; i += 1)
                result[index + i] = pivot.memory[i];

            index += pivot.length;
        }
    }

    for (pxiword i = 0; i < suffix.length; i += 1)
        result[index + i] = suffix.memory[i];

    index += suffix.length;

    return (PxString32) {
        .memory = result,
        .length = length,
    };
}

#endif // PX_STRING_LIST_C
