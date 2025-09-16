base="pax/core/base/export.c"
memory="pax/core/memory/export.c"
string="pax/core/string/export.c"
format="pax/core/format/export.c"
stream="pax/core/stream/export.c"

network="pax/core/network/export.c"

src="$base $memory $string $format $stream $network"
dir="pax/core/network/test"

gcc -g --std=c99 $network $dir/address_ip4.c -o network_address_ip4.exe
gcc -g --std=c99 $network $dir/address_ip6.c -o network_address_ip6.exe
gcc -g --std=c99 $network $dir/address.c     -o network_address.exe

gcc -g --std=c99 $network $dir/udp_server.c  -o network_udp_server.exe
gcc -g --std=c99 $network $dir/udp_client.c  -o network_udp_client.exe

gcc -g --std=c99 $network $dir/tcp_server.c  -o network_tcp_server.exe
gcc -g --std=c99 $network $dir/tcp_client.c  -o network_tcp_client.exe
