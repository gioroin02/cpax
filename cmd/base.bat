echo off

call cmd\clean.bat

set "base=pax\core\base\export.c"

set "pax=%base%"

set "pax=%pax%"
set "dir=pax\core\base\test"

zig cc --std=c99 %pax% "%dir%\number.c" -o base_number.exe
zig cc --std=c99 %pax% "%dir%\memory.c" -o base_memory.exe
