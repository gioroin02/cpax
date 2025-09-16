echo off

call cmd\clean.bat

set "string=pax\core\string\export.c"

set "src=%string%"
set "dir=pax\core\string\test"

zig cc --std=c99 %string% "%dir%\string8.c" -o string_string8.exe
