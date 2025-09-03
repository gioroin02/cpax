base="pax/core/base/export.c"
memory="pax/core/memory/export.c"
string="pax/core/string/export.c"
format="pax/core/format/export.c"
stream="pax/core/stream/export.c"
storage="pax/core/storage/export.c"

pax="$base $memory $string $format $stream $storage"

pax="$pax"
dir="pax/core/storage/test"

gcc --std=c99 $pax $dir/path.c -o storage_path.exe
