base="pax/core/base/export.c"

memory="pax/core/memory/export.c"

src="$base $memory"
dir="pax/core/memory/test"

gcc -g --std=c99 $src $dir/order.c   -o memory_order.exe
gcc -g --std=c99 $src $dir/system.c  -o memory_system.exe
gcc -g --std=c99 $src $dir/buffer8.c -o memory_buffer8.exe
