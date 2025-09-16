console="pax/core/console/export.c"
time="pax/core/time/export.c"
structure="pax/core/structure/export.c"

src="$console $time $structure"
dir="pax/core/console/test"

gcc -g --std=c99 $src $dir/escape.c  -o console_escape.exe
gcc -g --std=c99 $src $dir/buttons.c -o console_buttons.exe
gcc -g --std=c99 $src $dir/game.c    -o console_game.exe
