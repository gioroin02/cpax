base="pax/core/base/export.c"
memory="pax/core/memory/export.c"

structure="pax/core/structure/export.c"

src="$base $memory $structure"
dir="pax/core/structure/test"

gcc -g --std=c99 $src $dir/queue.c -o structure_queue.exe
