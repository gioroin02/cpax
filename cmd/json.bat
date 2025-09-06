echo off

call cmd\clean.bat

set "base=pax\core\base\export.c"
set "memory=pax\core\memory\export.c"
set "string=pax\core\string\export.c"
set "format=pax\core\format\export.c"
set "stream=pax\core\stream\export.c"
set "structure=pax\core\structure\export.c"
set "json=pax\encoding\json\export.c"

set "pax=%base% %memory% %string% %format% %stream% %structure% %json%"

set "pax=%pax%"
set "dir=pax\encoding\json\test"

zig cc --std=c99 %pax% "%dir%\token.c"  -o json_token.exe
zig cc --std=c99 %pax% "%dir%\event.c"  -o json_event.exe
zig cc --std=c99 %pax% "%dir%\reader.c" -o json_reader.exe
zig cc --std=c99 %pax% "%dir%\writer.c" -o json_writer.exe
