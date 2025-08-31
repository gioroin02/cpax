set base="src/pax/base/export.c"

set pax="$base"

set src="$pax"
set dir="src/pax/base/test"

zig cc --std=c99 $src "$dir/number.c" -o base_number.exe
zig cc --std=c99 $src "$dir/memory.c" -o base_memory.exe
