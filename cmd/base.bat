echo off

call cmd\clean.bat

set "base=src\pax\base\export.c"

set "src=%base%"
set "dir=src\pax\base\test"

zig cc --std=c99 %src% "%dir%\number.c" -o base_number.exe
zig cc --std=c99 %src% "%dir%\memory.c" -o base_memory.exe
