echo off

call cmd\clean.bat

set "format=pax\core\format\export.c"

set "src=%format%"
set "dir=pax\core\format\test"

zig cc --std=c99 %src% "%dir%\unsigned.c" -o format_unsigned.exe
