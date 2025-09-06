base="pax/core/base/export.c"
memory="pax/core/memory/export.c"

pax="$base $memory"

pax=$pax
dir="pax/core/memory/test"

gcc -g --std=c99 $pax $dir/order.c  -o memory_order.exe
gcc -g --std=c99 $pax $dir/system.c -o memory_system.exe
