echo off

call cmd\clean.bat

set "base=src\pax\base\export.c"
set "memory=src\pax\memory\export.c"
set "string=src\pax\string\export.c"
set "format=src\pax\format\export.c"
set "stream=src\pax\stream\export.c"
set "network=src\pax\network\export.c"

set "pax=%base% %memory% %string% %format% %stream% %network%"

set "winsock=-lws2_32"

set "src=%pax%"
set "lib=%winsock%"
set "dir=src\pax\network\test"

zig cc --std=c99 %src% "%dir%\address_ip4.c" %lib% -o network_address_ip4.exe
zig cc --std=c99 %src% "%dir%\address_ip6.c" %lib% -o network_address_ip6.exe
zig cc --std=c99 %src% "%dir%\address.c"     %lib% -o network_address.exe

zig cc --std=c99 %src% "%dir%\udp_server.c"  %lib% -o network_udp_server.exe
zig cc --std=c99 %src% "%dir%\udp_client.c"  %lib% -o network_udp_client.exe

zig cc --std=c99 %src% "%dir%\tcp_server.c"  %lib% -o network_tcp_server.exe
zig cc --std=c99 %src% "%dir%\tcp_client.c"  %lib% -o network_tcp_client.exe
