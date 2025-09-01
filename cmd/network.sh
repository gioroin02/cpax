base="src/pax/base/export.c"
memory="src/pax/memory/export.c"
string="src/pax/string/export.c"
format="src/pax/format/export.c"
stream="src/pax/stream/export.c"
network="src/pax/network/export.c"

pax="$base $memory $string $format $stream $network"

src="$pax"
dir="src/pax/network/test"

gcc --std=c99 $src $dir/address_ip4.c -o network_address_ip4.exe
gcc --std=c99 $src $dir/address_ip6.c -o network_address_ip6.exe
gcc --std=c99 $src $dir/address.c     -o network_address.exe

gcc --std=c99 $src $dir/udp_server.c  -o network_udp_server.exe
gcc --std=c99 $src $dir/udp_client.c  -o network_udp_client.exe

gcc --std=c99 $src $dir/tcp_server.c  -o network_tcp_server.exe
gcc --std=c99 $src $dir/tcp_client.c  -o network_tcp_client.exe
