base="pax/core/base/export.c"

pax=$base

pax=$pax
dir="pax/core/base/test"

gcc --std=c99 $pax $dir/number.c -o base_number.exe
gcc --std=c99 $pax $dir/memory.c -o base_memory.exe
