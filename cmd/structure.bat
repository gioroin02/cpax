echo off

call cmd\clean.bat

set "base=pax\core\base\export.c"
set "structure=pax\core\structure\export.c"

set "pax=%base% %structure%"

set "memory=pax\core\memory\export.c"

set "pax=%pax% %memory%"
set "dir=pax\core\structure\test"

zig cc --std=c99 %pax% "%dir%\queue.c" %lib% -o structure_queue.exe
