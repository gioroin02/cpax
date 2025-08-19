echo off

call cmd\clean.bat

set "base=src\pax\base\export.c"
set "memory=src\pax\memory\export.c"
set "string=src\pax\string\export.c"
set "format=src\pax\format\export.c"
set "stream=src\pax\stream\export.c"
set "json=src\pax\json\export.c"

set "pax=%base% %memory% %string% %format% %stream% %json%"

set "src=%pax%"
set "dir=src\pax\json\test"

zig cc --std=c99 %src% "%dir%\token.c" -o json_token.exe
