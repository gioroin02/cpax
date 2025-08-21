echo off

call cmd\clean.bat

set "base=src\pax\base\export.c"
set "memory=src\pax\memory\export.c"
set "string=src\pax\string\export.c"
set "format=src\pax\format\export.c"
set "stream=src\pax\stream\export.c"
set "structure=src\pax\structure\export.c"
set "json=src\pax\json\export.c"

set "pax=%base% %memory% %string% %format% %stream% %structure% %json%"

set "src=%pax%"
set "dir=src\pax\json\test"

zig cc --std=c99 %src% "%dir%\token.c"  -o json_token.exe
zig cc --std=c99 %src% "%dir%\event.c"  -o json_event.exe
zig cc --std=c99 %src% "%dir%\reader.c" -o json_reader.exe
zig cc --std=c99 %src% "%dir%\writer.c" -o json_writer.exe
