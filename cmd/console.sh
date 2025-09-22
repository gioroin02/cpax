base="pax/core/base/export.c"
memory="pax/core/memory/export.c"
string="pax/core/string/export.c"
format="pax/core/format/export.c"
stream="pax/core/stream/export.c"

console="pax/core/console/export.c"

process="pax/core/process/export.c"
time="pax/core/time/export.c"
structure="pax/core/structure/export.c"

pthread="-pthread"
math="-lm"

src="$base $memory $string $format $stream $console"
lib="$math $pthread"
dir="pax/core/console/test"

gcc -g --std=c99 $src $dir/escape.c  -o console_escape.exe
gcc -g --std=c99 $src $dir/message.c -o console_message.exe
gcc -g --std=c99 $src $dir/queue.c   -o console_queue.exe

gcc -g --std=c99 $src $process $time $structure $dir/game.c $lib -o console_game.exe
