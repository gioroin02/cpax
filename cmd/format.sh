base="pax/core/base/export.c"
memory="pax/core/memory/export.c"
string="pax/core/string/export.c"

format="pax/core/format/export.c"

src="$base $memory $string $format"
dir="pax/core/format/test"

gcc -g --std=c99 $src $dir/unsigned.c -o format_unsigned.exe
gcc -g --std=c99 $src $dir/integer.c  -o format_integer.exe
gcc -g --std=c99 $src $dir/boolean.c  -o format_boolean.exe
gcc -g --std=c99 $src $dir/printing.c -o format_printing.exe
