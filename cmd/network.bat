echo off

call cmd\clean.bat

set "base=src\pax\base\export.c"
set "memory=src\pax\memory\export.c"
set "string=src\pax\string\export.c"
set "format=src\pax\format\export.c"
set "stream=src\pax\stream\export.c"
set "network=src\pax\network\export.c"

set "winsock=-lws2_32"

set "src=%base% %memory% %string% %format% %stream% %network%"
set "lib=%winsock%"
set "dir=src\pax\network\test"

zig cc --std=c99 %src% "%dir%\address_ip4.c" %lib% -o bin\network_address_ip4.exe
