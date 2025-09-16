base="pax/core/base/export.c"
memory="pax/core/memory/export.c"

string="pax/core/string/export.c"

src="$base $memory $string"
dir="pax/core/string/test"

gcc -g --std=c99 $src $dir/string8.c -o string_string8.exe
