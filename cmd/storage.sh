base="src/pax/base/export.c"
memory="src/pax/memory/export.c"
string="src/pax/string/export.c"
format="src/pax/format/export.c"
stream="src/pax/stream/export.c"
storage="src/pax/storage/export.c"

pax="$base $memory $string $format $stream $storage"

src="$pax"
dir="src/pax/storage/test"

gcc --std=c99 $src $dir/path.c -o storage_path.exe
