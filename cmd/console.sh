base="pax/core/base/export.c"
memory="pax/core/memory/export.c"
string="pax/core/string/export.c"
format="pax/core/format/export.c"
stream="pax/core/stream/export.c"
storage="pax/core/storage/export.c"
console="pax/core/console/export.c"

pax="$base $memory $string $format $stream $storage $console"

structure="pax/core/structure/export.c"

pax="$pax $structure"
dir="pax/core/console/test"

gcc -g --std=c99 $pax $dir/console.c  -o console_console.exe
gcc -g --std=c99 $pax $dir/sequence.c -o console_sequence.exe
gcc -g --std=c99 $pax $dir/pattern.c  -o console_pattern.exe
