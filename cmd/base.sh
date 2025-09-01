base="src/pax/base/export.c"

pax=$base

src=$pax
dir="src/pax/base/test"

gcc --std=c99 $src $dir/number.c -o base_number.exe
gcc --std=c99 $src $dir/memory.c -o base_memory.exe
