echo off

call cmd\clean.bat

set "base=pax\core\base\export.c"
set "memory=pax\core\memory\export.c"
set "string=pax\core\string\export.c"
set "format=pax\core\format\export.c"
set "stream=pax\core\stream\export.c"

set "console=pax\core\console\export.c"

set "process=pax\core\process\export.c"
set "time=pax\core\time\export.c"
set "structure=pax\core\structure\export.c"

set "src=%base% %memory% %string% %format% %stream% %console%"
set "dir=pax\core\console\test"

zig cc --std=c99 %src% "%dir%\escape.c"  -o console_escape.exe
zig cc --std=c99 %src% "%dir%\message.c" -o console_message.exe
zig cc --std=c99 %src% "%dir%\queue.c"   -o console_queue.exe

zig cc --std=c99 %src% %process% %time% %structure% "%dir%\game.c" -o console_game.exe
