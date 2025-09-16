echo off

call cmd\clean.bat

set "base=pax\core\base\export.c"
set "memory=pax\core\memory\export.c"

set "string=pax\core\string\export.c"

set "src=%base% %memory% %string%"
set "dir=pax\core\string\test"

zig cc --std=c99 %src% "%dir%\string8.c" -o string_string8.exe
