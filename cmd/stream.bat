echo off

call cmd\clean.bat

set "base=src\pax\base\export.c"
set "string=src\pax\string\export.c"
set "stream=src\pax\stream\export.c"

set "pax=%base% %string% %stream%"

set "src=%pax%"
set "dir=src\pax\stream\test"

zig cc --std=c99 %src% "%dir%\reader.c" -o stream_reader.exe
