base="pax/core/base/export.c"
string="pax/core/string/export.c"
format="pax/core/format/export.c"
stream="pax/core/stream/export.c"

pax="$base $string $format $stream"

memory="pax/core/memory/export.c"

pax="$pax $memory"
dir="pax/core/stream/test"

gcc --std=c99 $pax $dir/reader.c  -o stream_reader.exe
gcc --std=c99 $pax $dir/buffer8.c -o stream_buffer8.exe
