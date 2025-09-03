base="pax/core/base/export.c"
string="pax/core/string/export.c"
format="pax/core/format/export.c"

pax="$base $string $format"

memory="pax/core/memory/export.c"

pax="$pax $memory"
dir="pax/core/format/test"

gcc --std=c99 $pax $dir/string8.c -o format_string8.exe
