base="pax/core/base/export.c"
string="pax/core/string/export.c"

pax="$base $string"

pax="$pax"
dir="pax/core/string/test"

gcc --std=c99 $pax $dir/string8.c -o string_string8.exe
gcc --std=c99 $pax $dir/list.c    -o string_list.exe
gcc --std=c99 $pax $dir/ascii.c   -o string_ascii.exe
