echo off

call cmd\clean.bat

set "base=src\pax\base\export.c"
set "stream=src\pax\stream\export.c"

set "src=%base% %stream%"
set "dir=src\pax\stream\test"

zig cc --std=c99 %src% "%dir%\reader.c" -o stream_reader.exe
