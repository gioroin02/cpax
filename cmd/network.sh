base="pax/core/base/export.c"
memory="pax/core/memory/export.c"
string="pax/core/string/export.c"
format="pax/core/format/export.c"
stream="pax/core/stream/export.c"
network="pax/core/network/export.c"

pax="$base $memory $string $format $stream $network"

pax="$pax"
dir="pax/core/network/test"

gcc --std=c99 $pax $dir/address_ip4.c -o network_address_ip4.exe
gcc --std=c99 $pax $dir/address_ip6.c -o network_address_ip6.exe
gcc --std=c99 $pax $dir/address.c     -o network_address.exe

gcc --std=c99 $pax $dir/udp_server.c  -o network_udp_server.exe
gcc --std=c99 $pax $dir/udp_client.c  -o network_udp_client.exe

gcc --std=c99 $pax $dir/tcp_server.c  -o network_tcp_server.exe
gcc --std=c99 $pax $dir/tcp_client.c  -o network_tcp_client.exe
