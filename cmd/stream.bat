echo off

call cmd\clean.bat

set "stream=pax\core\stream\export.c"

set "src=%stream%"
set "dir=pax\core\stream\test"

zig cc --std=c99 %src% "%dir%\reader.c" -o stream_reader.exe
