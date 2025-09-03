echo off

call cmd\clean.bat

set "base=pax\core\base\export.c"
set "memory=pax\core\memory\export.c"
set "string=pax\core\string\export.c"
set "format=pax\core\format\export.c"
set "stream=pax\core\stream\export.c"
set "network=pax\core\network\export.c"

set "pax=%base% %memory% %string% %format% %stream% %network%"

set "winsock=-lws2_32"

set "pax=%pax%"
set "lib=%winsock%"
set "dir=pax\core\network\test"

zig cc --std=c99 %pax% "%dir%\address_ip4.c" %lib% -o network_address_ip4.exe
zig cc --std=c99 %pax% "%dir%\address_ip6.c" %lib% -o network_address_ip6.exe
zig cc --std=c99 %pax% "%dir%\address.c"     %lib% -o network_address.exe

zig cc --std=c99 %pax% "%dir%\udp_server.c"  %lib% -o network_udp_server.exe
zig cc --std=c99 %pax% "%dir%\udp_client.c"  %lib% -o network_udp_client.exe

zig cc --std=c99 %pax% "%dir%\tcp_server.c"  %lib% -o network_tcp_server.exe
zig cc --std=c99 %pax% "%dir%\tcp_client.c"  %lib% -o network_tcp_client.exe
