echo off

call cmd\clean.bat

set "base=pax\core\base\export.c"
set "string=pax\core\string\export.c"
set "format=pax\core\format\export.c"
set "stream=pax\core\stream\export.c"
set "logging=pax\core\logging\export.c"

set "pax=%base% %string% %format% %stream% %logging%"

set "memory=pax\core\memory\export.c"
set "console=pax\core\console\export.c"

set "pax=%pax% %memory% %console%"
set "dir=pax\core\logging\test"

zig cc --std=c99 %pax% "%dir%\logger.c" -o logging_logger.exe
