echo off

call cmd\clean.bat

set "storage=pax\core\storage\export.c"

set "src=%storage%"
set "dir=pax\core\storage\test"

zig cc --std=c99 %src% "%dir%\path.c"    -o storage_path.exe
zig cc --std=c99 %src% "%dir%\read.c"    -o storage_read.exe
zig cc --std=c99 %src% "%dir%\destroy.c" -o storage_destroy.exe
