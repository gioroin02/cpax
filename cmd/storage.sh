storage="pax/core/storage/export.c"

src="$storage"
dir="pax/core/storage/test"

gcc -g --std=c99 $src $dir/path.c    -o storage_path.exe
gcc -g --std=c99 $src $dir/read.c    -o storage_read.exe
gcc -g --std=c99 $src $dir/destroy.c -o storage_destroy.exe
