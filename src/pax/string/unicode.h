#ifndef PX_STRING_UNICODE_H
#define PX_STRING_UNICODE_H

#include "import.h"

pxbool8
pxUnicodeIsValid(pxint32 value);

pxbool8
pxUnicodeIsSurrogate(pxint32 value);

pxbool8
pxUnicodeIsSurrogateLow(pxint32 value);

pxbool8
pxUnicodeIsSurrogateHigh(pxint32 value);

pxbool8
pxUnicodeIsAscii(pxint32 value);

pxbool8
pxAsciiIsSpace(pxint32 value);

#endif // PX_STRING_UNICODE_H
