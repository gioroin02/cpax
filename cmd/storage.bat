echo off

call cmd\clean.bat

set "base=src\pax\base\export.c"
set "memory=src\pax\memory\export.c"
set "string=src\pax\string\export.c"
set "format=src\pax\format\export.c"
set "stream=src\pax\stream\export.c"
set "storage=src\pax\storage\export.c"

set "pax=%base% %memory% %string% %format% %stream% %storage%"

set "src=%pax%"
set "dir=src\pax\storage\test"

zig cc --std=c99 %src% "%dir%\path.c" %lib% -o storage_path.exe
