echo off

call cmd\clean.bat

set "base=pax\core\base\export.c"

set "memory=pax\core\memory\export.c"

set "src=%base% %memory%"
set "dir=pax\core\memory\test"

zig cc --std=c99 %src% "%dir%\order.c"   -o memory_order.exe
zig cc --std=c99 %src% "%dir%\system.c"  -o memory_system.exe
zig cc --std=c99 %src% "%dir%\buffer8.c" -o memory_buffer8.exe
