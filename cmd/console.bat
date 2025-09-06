echo off

call cmd\clean.bat

set "base=pax\core\base\export.c"
set "memory=pax\core\memory\export.c"
set "string=pax\core\string\export.c"
set "format=pax\core\format\export.c"
set "stream=pax\core\stream\export.c"
set "storage=pax\core\storage\export.c"
set "console=pax\core\console\export.c"

set "pax=%base% %memory% %string% %format% %stream% %storage% %console%"

set "pax=%pax%"
set "dir=pax\core\console\test"

zig cc --std=c99 %pax% "%dir%\console.c"  -o console_console.exe
zig cc --std=c99 %pax% "%dir%\sequence.c" -o console_sequence.exe
