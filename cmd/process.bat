echo off

call cmd\clean.bat

set "base=pax\core\base\export.c"
set "memory=pax\core\memory\export.c"

set "process=pax\core\process\export.c"

set "src=%base% %memory% %process%"
set "dir=pax\core\process\test"

zig cc --std=c99 %src% "%dir%\thread.c" -o process_thread.exe
zig cc --std=c99 %src% "%dir%\system.c" -o process_system.exe
