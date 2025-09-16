structure="pax/core/structure/export.c"

src="$structure"
dir="pax/core/structure/test"

gcc -g --std=c99 $src $dir/queue.c -o structure_queue.exe
