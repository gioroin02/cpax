echo off

call cmd\clean.bat

set "base=pax\core\base\export.c"
set "string=pax\core\string\export.c"

set "pax=%base% %string%"

set "pax=%pax%"
set "dir=pax\core\string\test"

zig cc --std=c99 %pax% "%dir%\string8.c" -o string_string8.exe
zig cc --std=c99 %pax% "%dir%\list.c"    -o string_list.exe
zig cc --std=c99 %pax% "%dir%\ascii.c"   -o string_ascii.exe
