base="pax/core/base/export.c"
memory="pax/core/memory/export.c"
string="pax/core/string/export.c"

stream="pax/core/stream/export.c"

src="$base $memory $string $stream"
dir="pax/core/stream/test"

gcc -g --std=c99 $src $dir/source.c -o stream_source.exe
gcc -g --std=c99 $src $dir/target.c -o stream_target.exe
