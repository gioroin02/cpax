echo off

call cmd\clean.bat

set "base=pax\core\base\export.c"
set "memory=pax\core\memory\export.c"
set "string=pax\core\string\export.c"

set "format=pax\core\format\export.c"

set "src=%base% %memory% %string% %format%"
set "dir=pax\core\format\test"

zig cc --std=c99 %src% "%dir%\unsigned.c" -o format_unsigned.exe
zig cc --std=c99 %src% "%dir%\integer.c"  -o format_integer.exe
zig cc --std=c99 %src% "%dir%\boolean.c"  -o format_boolean.exe
zig cc --std=c99 %src% "%dir%\printing.c" -o format_printing.exe
