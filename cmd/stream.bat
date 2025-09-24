echo off

call cmd\clean.bat

set "base=pax\core\base\export.c"
set "memory=pax\core\memory\export.c"
set "string=pax\core\string\export.c"

set "stream=pax\core\stream\export.c"

set "src=%base% %memory% %string% %stream%"
set "dir=pax\core\stream\test"

zig cc --std=c99 %src% "%dir%\source.c" -o stream_source.exe
zig cc --std=c99 %src% "%dir%\target.c" -o stream_target.exe
