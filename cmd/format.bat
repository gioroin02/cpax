echo off

call cmd\clean.bat

set "base=src\pax\base\export.c"
set "string=src\pax\string\export.c"
set "format=src\pax\format\export.c"

set "pax=%base% %string% %format%"

set "memory=src\pax\memory\export.c"

set "src=%pax% %memory%"
set "dir=src\pax\format\test"

zig cc --std=c99 %src% "%dir%\string8.c" -o format_string8.exe
