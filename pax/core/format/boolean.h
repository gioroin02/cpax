#ifndef PX_CORE_FORMAT_BOOLEAN_H
#define PX_CORE_FORMAT_BOOLEAN_H

#include "config.h"

pxiword
pxBooleanDigits(pxbword value, PxFmtFlag flags);

/* Memory */

pxiword
pxMemory8WriteBoolean(pxu8* memory, pxiword length, pxbword value, PxFmtFlag flags);

pxiword
pxMemory8ReadBoolean(pxu8* memory, pxiword length, pxbword* value, PxFmtFlag flags);

pxiword
pxMemory16WriteBoolean(pxu16* memory, pxiword length, pxbword value, PxFmtFlag flags);

pxiword
pxMemory16ReadBoolean(pxu16* memory, pxiword length, pxbword* value, PxFmtFlag flags);

pxiword
pxMemory32WriteBoolean(pxu32* memory, pxiword length, pxbword value, PxFmtFlag flags);

pxiword
pxMemory32ReadBoolean(pxu32* memory, pxiword length, pxbword* value, PxFmtFlag flags);

/* String */

PxString8
pxString8FromBoolean(PxArena* arena, pxbword value, PxFmtFlag flags);

pxb8
pxBooleanFromString8(PxString8 string, pxbword* value, PxFmtFlag flags);

PxString16
pxString16FromBoolean(PxArena* arena, pxbword value, PxFmtFlag flags);

pxb8
pxBooleanFromString16(PxString16 string, pxbword* value, PxFmtFlag flags);

PxString32
pxString32FromBoolean(PxArena* arena, pxbword value, PxFmtFlag flags);

pxb8
pxBooleanFromString32(PxString32 string, pxbword* value, PxFmtFlag flags);

/* Buffer */

pxiword
pxBuffer8WriteBooleanHead(PxBuffer8* self, pxbword value, PxFmtFlag flags);

pxiword
pxBuffer8WriteBooleanTail(PxBuffer8* self, pxbword value, PxFmtFlag flags);

pxiword
pxBuffer16WriteBooleanHead(PxBuffer16* self, pxbword value, PxFmtFlag flags);

pxiword
pxBuffer16WriteBooleanTail(PxBuffer16* self, pxbword value, PxFmtFlag flags);

pxiword
pxBuffer32WriteBooleanHead(PxBuffer32* self, pxbword value, PxFmtFlag flags);

pxiword
pxBuffer32WriteBooleanTail(PxBuffer32* self, pxbword value, PxFmtFlag flags);

/* Writer */

pxiword
pxWriterNextBoolean(PxWriter* self, pxbword, PxFmtFlag flags);

#endif // PX_CORE_FORMAT_BOOLEAN_H
