base="pax/core/base/export.c"
memory="pax/core/memory/export.c"
string="pax/core/string/export.c"
format="pax/core/format/export.c"
stream="pax/core/stream/export.c"

storage="pax/core/storage/export.c"

src="$base $memory $string $format $stream $storage"
dir="pax/core/storage/test"

gcc -g --std=c99 $src $dir/path.c    -o storage_path.exe
gcc -g --std=c99 $src $dir/read.c    -o storage_read.exe
gcc -g --std=c99 $src $dir/destroy.c -o storage_destroy.exe
