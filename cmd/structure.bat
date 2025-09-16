echo off

call cmd\clean.bat

set "structure=pax\core\structure\export.c"

set "src=%structure%"
set "dir=pax\core\structure\test"

zig cc --std=c99 %src% "%dir%\queue.c" -o structure_queue.exe
