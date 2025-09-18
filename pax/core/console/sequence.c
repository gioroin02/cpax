#ifndef PX_CORE_CONSOLE_SEQUENCE_C
#define PX_CORE_CONSOLE_SEQUENCE_C

#include "sequence.h"

pxb8
pxAnsiSequenceGroupInsert(PxAnsiSequenceGroup* self, pxuword value)
{
    pxiword index = self->size;

    if (index < 0 || index >= PX_ESCAPE_VALUES)
        return 0;

    self->size += 1;

    self->values[index] = value;

    return 1;
}

pxb8
pxAnsiSequenceRead(PxAnsiSequence* self, pxiword group, pxiword index, pxuword* value)
{
    if (group < 0 || group >= self->size)
        return 0;

    PxAnsiSequenceGroup* child = &self->groups[group];

    if (index < 0 || index >= child->size)
        return 0;

    if (value != 0) *value = child->values[index];

    return 1;
}

pxuword
pxAnsiSequenceReadOr(PxAnsiSequence* self, pxiword group, pxiword index, pxuword value)
{
    if (group < 0 || group >= self->size)
        return value;

    PxAnsiSequenceGroup* child = &self->groups[group];

    if (index < 0 || index >= child->size)
        return value;

    return child->values[index];
}

pxb8
pxAnsiSequenceGroupFromString8(PxString8 string, PxAnsiSequenceGroup* value)
{
    PxString8 left  = {0};
    PxString8 right = string;

    while (right.length > 0) {
        pxString8Split(right, pxs8(":"), &left, &right);

        PxFormatRadix radix = PX_FORMAT_RADIX_10;
        PxFormatFlag  flags = PX_FORMAT_FLAG_NONE;

        pxuword item  = 0;
        pxb8    state = 0;

        state = pxUnsignedFromString8(left, &item, radix, flags);

        if (left.length >= 0 && state != 0)
            pxAnsiSequenceGroupInsert(value, item);
        else
            return 0;
    }

    return 1;
}

pxb8
pxAnsiSequenceFromString8(PxString8 string, PxAnsiSequence* value)
{
    PxAnsiSequence temp = {0};

    pxiword index = 2;

    if (string.length <= index) return 0;

    if (string.memory[0] != 0x1b) return 0;
    if (string.memory[1] != 0x5b) return 0;

    PxString8 left  = {0};
    PxString8 right = pxString8Slice(string, index, string.length - 1);

    pxb8 state = 0;

    while (right.length > 0) {
        pxString8Split(right, pxs8(";"), &left, &right);

        PxAnsiSequenceGroup* group = 0;

        if (temp.size >= 0 && temp.size < PX_ESCAPE_GROUPS) {
            group = &temp.groups[temp.size];
            state = pxAnsiSequenceGroupFromString8(left, group);

            if (state == 0) return 0;

            temp.size += 1;
        }
    }

    temp.func = string.memory[string.length - 1];

    if (value != 0) *value = temp;

    return 1;
}

#endif // PX_CORE_CONSOLE_SEQUENCE_C
