base="pax/core/base/export.c"

pax=$base

pax=$pax
dir="pax/core/base/test"

gcc -g --std=c99 $pax $dir/number.c -o base_number.exe
gcc -g --std=c99 $pax $dir/memory.c -o base_memory.exe
