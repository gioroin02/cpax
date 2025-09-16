echo off

call cmd\clean.bat

set "network=pax\core\network\export.c"

set "winsock=-lws2_32"

set "src=%network%"
set "lib=%winsock%"
set "dir=pax\core\network\test"

zig cc --std=c99 %src% "%dir%\address_ip4.c" %lib% -o network_address_ip4.exe
zig cc --std=c99 %src% "%dir%\address_ip6.c" %lib% -o network_address_ip6.exe
zig cc --std=c99 %src% "%dir%\address.c"     %lib% -o network_address.exe

zig cc --std=c99 %src% "%dir%\udp_server.c"  %lib% -o network_udp_server.exe
zig cc --std=c99 %src% "%dir%\udp_client.c"  %lib% -o network_udp_client.exe

zig cc --std=c99 %src% "%dir%\tcp_server.c"  %lib% -o network_tcp_server.exe
zig cc --std=c99 %src% "%dir%\tcp_client.c"  %lib% -o network_tcp_client.exe
