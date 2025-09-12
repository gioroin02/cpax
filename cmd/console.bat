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

set "time=pax\core\time\export.c"
set "structure=pax\core\structure\export.c"

set "pax=%pax% %time% %structure%"
set "dir=pax\core\console\test"

zig cc --std=c99 %pax% "%dir%\escape.c"  -o console_escape.exe
zig cc --std=c99 %pax% "%dir%\buttons.c" -o console_buttons.exe
zig cc --std=c99 %pax% "%dir%\game.c"    -o console_game.exe
