echo off

call cmd\clean.bat

set "base=pax\core\base\export.c"
set "memory=pax\core\memory\export.c"
set "string=pax\core\string\export.c"
set "format=pax\core\format\export.c"
set "stream=pax\core\stream\export.c"

set "storage=pax\core\storage\export.c"

set "src=%base% %memory% %string% %format% %stream% %storage%"
set "dir=pax\core\storage\test"

zig cc --std=c99 %src% "%dir%\path.c"    -o storage_path.exe
zig cc --std=c99 %src% "%dir%\read.c"    -o storage_read.exe
zig cc --std=c99 %src% "%dir%\destroy.c" -o storage_destroy.exe
