base="pax/core/base/export.c"
memory="pax/core/memory/export.c"
string="pax/core/string/export.c"
format="pax/core/format/export.c"

stream="pax/core/stream/export.c"

src="$base $memory $string $format $stream"
dir="pax/core/stream/test"

gcc -g --std=c99 $src $dir/reader.c  -o stream_reader.exe
gcc -g --std=c99 $src $dir/command.c -o stream_command.exe
