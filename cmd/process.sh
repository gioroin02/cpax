base="pax/core/base/export.c"
memory="pax/core/memory/export.c"

process="pax/core/process/export.c"

pthread="-pthread"

src="$base $memory $process"
lib="$pthread"
dir="pax/core/process/test"

gcc --std=c99 $src $dir/thread.c $lib -o process_thread.exe
gcc --std=c99 $src $dir/system.c $lib -o process_system.exe
