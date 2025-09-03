base="pax/core/base/export.c"
memory="pax/core/memory/export.c"
string="pax/core/string/export.c"
format="pax/core/format/export.c"
stream="pax/core/stream/export.c"
structure="pax/core/structure/export.c"
json="pax/core/json/export.c"

pax="$base $memory $string $format $stream $structure $json"

pax="$pax"
dir="pax/core/json/test"

zig cc --std=c99 $pax $dir/token.c  -o json_token.exe
zig cc --std=c99 $pax $dir/event.c  -o json_event.exe
zig cc --std=c99 $pax $dir/reader.c -o json_reader.exe
zig cc --std=c99 $pax $dir/writer.c -o json_writer.exe
