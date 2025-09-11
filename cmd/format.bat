echo off

call cmd\clean.bat

set "base=pax\core\base\export.c"
set "string=pax\core\string\export.c"
set "format=pax\core\format\export.c"

set "pax=%base% %string% %format%"

set "memory=pax\core\memory\export.c"

set "pax=%pax% %memory%"
set "dir=pax\core\format\test"

zig cc --std=c99 %pax% "%dir%\string8.c" -o format_string8.exe
zig cc --std=c99 %pax% "%dir%\builder.c" -o format_builder.exe
