echo off

call cmd\clean.bat

set "base=src\pax\base\export.c"
set "string=src\pax\string\export.c"

set "src=%base% %string%"
set "dir=src\pax\string\test"

zig cc --std=c99 %src% "%dir%\string8.c" -o string_string8.exe
