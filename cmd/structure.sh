base="pax/core/base/export.c"
structure="pax/core/structure/export.c"

pax="$base $structure"

memory="pax/core/memory/export.c"

pax="$pax $memory"
dir="pax/core/structure/test"

gcc --std=c99 $pax $dir/queue.c -o structure_queue.exe
