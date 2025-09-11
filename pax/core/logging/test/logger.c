#include "../export.h"

#include "../../console/export.h"

int
main(int argc, char** argv)
{
    PxArena arena = pxMemoryReserve(16);

    PxConsole console = pxConsoleCreate(&arena, 1024);
    PxWriter  writer  = pxConsoleWriter(console, &arena, 1024);

    PxLogger logger = pxLoggerReserve(&arena, 1024, writer,
        PX_REPORT_LEVEL_WARN, PX_REPORT_FLAG_COLORS);

    pxLoggerReport(&logger, "level = WARN\n", (PxBuilderCmd) {0});

    pxLoggerTrace(&logger, "TRACE [${0}, ${1}, ${2}, ${3}, ${4}, ${5}]\n",
        pxBuilderCmdInteger(10, PX_FORMAT_OPTION_NONE, 1),
        pxBuilderCmdInteger(10, PX_FORMAT_OPTION_NONE, 2),
        pxBuilderCmdInteger(10, PX_FORMAT_OPTION_NONE, 3),
        pxBuilderCmdInteger(10, PX_FORMAT_OPTION_NONE, 4),
        pxBuilderCmdInteger(10, PX_FORMAT_OPTION_NONE, 5),
        pxBuilderCmdInteger(10, PX_FORMAT_OPTION_NONE, 6),
    );

    pxLoggerWarn(&logger, "WARN\n", (PxBuilderCmd) {0});

    pxLoggerFlush(&logger);
    pxLoggerSetLevel(&logger, PX_REPORT_LEVEL_TRACE);

    pxLoggerReport(&logger, "level = TRACE\n", (PxBuilderCmd) {0});

    pxLoggerTrace(&logger, "TRACE [${0}, ${1}, ${2}, ${3}, ${4}, ${5}]\n",
        pxBuilderCmdInteger(10, PX_FORMAT_OPTION_NONE, 1),
        pxBuilderCmdInteger(10, PX_FORMAT_OPTION_NONE, 2),
        pxBuilderCmdInteger(10, PX_FORMAT_OPTION_NONE, 3),
        pxBuilderCmdInteger(10, PX_FORMAT_OPTION_NONE, 4),
        pxBuilderCmdInteger(10, PX_FORMAT_OPTION_NONE, 5),
        pxBuilderCmdInteger(10, PX_FORMAT_OPTION_NONE, 6),
    );

    pxLoggerWarn(&logger, "WARN\n", (PxBuilderCmd) {0});

    pxLoggerFlush(&logger);
}
