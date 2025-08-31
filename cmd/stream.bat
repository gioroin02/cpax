echo off

call cmd\clean.bat

set "base=src\pax\base\export.c"
set "string=src\pax\string\export.c"
set "format=src\pax\format\export.c"
set "stream=src\pax\stream\export.c"

set "pax=%base% %string% %format% %stream%"

set "memory=src\pax\memory\export.c"

set "src=%pax% %memory%"
set "dir=src\pax\stream\test"

zig cc --std=c99 %src% "%dir%\reader.c"  -o stream_reader.exe
zig cc --std=c99 %src% "%dir%\buffer8.c" -o stream_buffer8.exe
