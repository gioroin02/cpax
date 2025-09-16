json="pax/encoding/json/export.c"

src="$json"
dir="pax/encoding/json/test"

zig cc --std=c99 $src $dir/token.c  -o json_token.exe
zig cc --std=c99 $src $dir/event.c  -o json_event.exe
zig cc --std=c99 $src $dir/reader.c -o json_reader.exe
zig cc --std=c99 $src $dir/writer.c -o json_writer.exe
