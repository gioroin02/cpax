stream="pax/core/stream/export.c"

src="$$stream"
dir="pax/core/stream/test"

gcc -g --std=c99 $src $dir/reader.c -o stream_reader.exe
