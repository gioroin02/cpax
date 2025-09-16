base="pax/core/base/export.c"

src=$base
dir="pax/core/base/test"

gcc -g --std=c99 $src $dir/number.c -o base_number.exe
gcc -g --std=c99 $src $dir/memory.c -o base_memory.exe
