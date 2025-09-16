format="pax/core/format/export.c"

src="$format"
dir="pax/core/format/test"

gcc -g --std=c99 $src $dir/unsigned.c -o format_unsigned.exe
