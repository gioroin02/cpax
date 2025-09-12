base="pax/core/base/export.c"
string="pax/core/string/export.c"

pax="$base $string"

pax="$pax"
dir="pax/core/string/test"

gcc -g --std=c99 $pax $dir/string8.c -o string_string8.exe
gcc -g --std=c99 $pax $dir/ascii.c   -o string_ascii.exe
