#include "../export.h"

#include "../../console/export.h"

int
main(int argc, char** argv)
{
    PxArena arena = pxMemoryReserve(16);

    PxConsole console = pxConsoleCreate(&arena);
    PxWriter  writer  = pxConsoleWriter(console, &arena, 1024);

    PxLogger logger = pxLoggerReserve(&arena, 1024, writer,
        PX_REPORT_LEVEL_WARN, PX_REPORT_FLAG_LEVEL | PX_REPORT_FLAG_COLOR);

    pxLoggerReport(&logger, "Level is \"warn\"\n\n", (PxBuilderCmd) {0});

    pxLoggerError(&logger, "IMPORTANT\n", (PxBuilderCmd) {0});

    pxLoggerInfo(&logger, "With args [${0}, ${1}, ${2}, ${3}, ${4}, ${5}]\n",
        pxBuilderCmdInteger(10, PX_FORMAT_OPTION_NONE, 1),
        pxBuilderCmdInteger(10, PX_FORMAT_OPTION_NONE, 2),
        pxBuilderCmdInteger(10, PX_FORMAT_OPTION_NONE, 3),
        pxBuilderCmdInteger(10, PX_FORMAT_OPTION_NONE, 4),
        pxBuilderCmdInteger(10, PX_FORMAT_OPTION_NONE, 5),
        pxBuilderCmdInteger(10, PX_FORMAT_OPTION_NONE, 6),
    );

    pxLoggerWarn(&logger, "No args\n", (PxBuilderCmd) {0});
    pxLoggerTrace(&logger, "No args\n", (PxBuilderCmd) {0});

    pxLoggerFlush(&logger);
    pxLoggerSetLevel(&logger, PX_REPORT_LEVEL_TRACE);

    pxLoggerReport(&logger, "\nlevel is \"trace\"\n\n", (PxBuilderCmd) {0});

    pxLoggerError(&logger, "IMPORTANT\n", (PxBuilderCmd) {0});

    pxLoggerInfo(&logger, "With args [${0}, ${1}, ${2}, ${3}, ${4}, ${5}]\n",
        pxBuilderCmdInteger(10, PX_FORMAT_OPTION_NONE, 1),
        pxBuilderCmdInteger(10, PX_FORMAT_OPTION_NONE, 2),
        pxBuilderCmdInteger(10, PX_FORMAT_OPTION_NONE, 3),
        pxBuilderCmdInteger(10, PX_FORMAT_OPTION_NONE, 4),
        pxBuilderCmdInteger(10, PX_FORMAT_OPTION_NONE, 5),
        pxBuilderCmdInteger(10, PX_FORMAT_OPTION_NONE, 6),
    );

    pxLoggerWarn(&logger, "No args\n", (PxBuilderCmd) {0});
    pxLoggerTrace(&logger, "No args\n", (PxBuilderCmd) {0});

    pxLoggerFlush(&logger);
}
