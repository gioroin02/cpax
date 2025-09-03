echo off

call cmd\clean.bat

set "base=pax\core\base\export.c"
set "memory=pax\core\memory\export.c"

set "pax=%base% %memory%"

set "pax=%pax%"
set "dir=pax\core\memory\test"

zig cc --std=c99 %pax% "%dir%\order.c"  -o memory_order.exe
zig cc --std=c99 %pax% "%dir%\system.c" -o memory_system.exe
