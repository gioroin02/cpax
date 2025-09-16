echo off

call cmd\clean.bat

set "base=pax\core\base\export.c"
set "memory=pax\core\memory\export.c"

set "structure=pax\core\structure\export.c"

set "src=%base% %memory% %structure%"
set "dir=pax\core\structure\test"

zig cc --std=c99 %src% "%dir%\queue.c" -o structure_queue.exe
