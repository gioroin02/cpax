base="src/pax/base/export.c"
memory="src/pax/memory/export.c"

pax="$base $memory"

src=$pax
dir="src/pax/memory/test"

gcc --std=c99 $src $dir/order.c  -o memory_order.exe
gcc --std=c99 $src $dir/system.c -o memory_system.exe
