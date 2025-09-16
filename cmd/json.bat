echo off

call cmd\clean.bat

set "json=pax\encoding\json\export.c"

set "src=%json%"
set "dir=pax\encoding\json\test"

zig cc --std=c99 %src% "%dir%\token.c"   -o json_token.exe
zig cc --std=c99 %src% "%dir%\message.c" -o json_message.exe
zig cc --std=c99 %src% "%dir%\reader.c"  -o json_reader.exe
zig cc --std=c99 %src% "%dir%\writer.c"  -o json_writer.exe
