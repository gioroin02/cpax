echo off

call cmd\clean.bat

set "base=pax\core\base\export.c"
set "string=pax\core\string\export.c"
set "format=pax\core\format\export.c"
set "stream=pax\core\stream\export.c"

set "pax=%base% %string% %format% %stream%"

set "memory=pax\core\memory\export.c"

set "pax=%pax% %memory%"
set "dir=pax\core\stream\test"

zig cc --std=c99 %pax% "%dir%\reader.c"  -o stream_reader.exe
zig cc --std=c99 %pax% "%dir%\buffer8.c" -o stream_buffer8.exe
