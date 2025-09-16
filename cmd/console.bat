echo off

call cmd\clean.bat

set "console=pax\core\console\export.c"
set "time=pax\core\time\export.c"
set "structure=pax\core\structure\export.c"

set "src=%console% %time% %structure%"
set "dir=pax\core\console\test"

zig cc --std=c99 %src% "%dir%\escape.c"  -o console_escape.exe
zig cc --std=c99 %src% "%dir%\buttons.c" -o console_buttons.exe
zig cc --std=c99 %src% "%dir%\game.c"    -o console_game.exe
