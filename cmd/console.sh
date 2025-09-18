base="pax/core/base/export.c"
memory="pax/core/memory/export.c"
string="pax/core/string/export.c"
format="pax/core/format/export.c"
stream="pax/core/stream/export.c"

console="pax/core/console/export.c"

time="pax/core/time/export.c"
structure="pax/core/structure/export.c"

src="$base $memory $string $format $stream $console"
dir="pax/core/console/test"

gcc -g --std=c99 $src $dir/sequence.c -o console_sequence.exe
gcc -g --std=c99 $src $dir/queue.c    -o console_queue.exe
