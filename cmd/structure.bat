echo off

call cmd\clean.bat

set "base=src\pax\base\export.c"
set "structure=src\pax\structure\export.c"

set "pax=%base% %structure%"

set "memory=src\pax\memory\export.c"

set "src=%pax% %memory%"
set "dir=src\pax\structure\test"

zig cc --std=c99 %src% "%dir%\queue.c" %lib% -o structure_queue.exe
