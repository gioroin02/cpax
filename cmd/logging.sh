base="pax/core/base/export.c"
string="pax/core/string/export.c"
format="pax/core/format/export.c"
stream="pax/core/stream/export.c"
logging="pax/core/logging/export.c"

pax="$base $string $format $stream $logging"

memory="pax/core/memory/export.c"
console="pax/core/console/export.c"

pax="$pax $memory $console"
dir="pax/core/logging/test"

gcc -g --std=c99 $pax $dir/logger.c -o logging_logger.exe
