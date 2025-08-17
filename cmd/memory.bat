echo off

call cmd\clean.bat

set "base=src\pax\base\export.c"
set "memory=src\pax\memory\export.c"

set "src=%base% %memory%"
set "dir=src\pax\memory\test"

zig cc --std=c99 %src% "%dir%\system.c" -o memory_system.exe
