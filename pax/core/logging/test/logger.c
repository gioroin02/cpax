#include "../export.h"

#include "../../console/export.h"

int
main(int argc, char** argv)
{
    PxArena arena = pxMemoryReserve(16);

    PxConsole console = pxConsoleCreate(&arena);
    PxWriter  writer  = pxWriterFromTarget(pxTargetFromConsole(console), &arena, 1024);

    PxLogger logger = pxLoggerMake(&writer, PX_REPORT_LEVEL_WARN,
        PX_REPORT_FLAG_LEVEL | PX_REPORT_FLAG_COLOR);

    pxLoggerPrint(&logger, pxs8("Level is \"WARN\"\n\n"));

    pxLoggerFatal(&logger, pxs8("No args\n"));
    pxLoggerError(&logger, pxs8("No args\n"));
    pxLoggerWarn(&logger,  pxs8("No args\n"));

    pxLoggerInfoFmt(&logger, pxs8("With args [${0}, ${1}, ${2}, ${3}, ${4}, ${5}]\n"),
        (PxPrintCmd[]) {
            pxPrintCmdInteger(1), pxPrintCmdInteger(2), pxPrintCmdInteger(3),
            pxPrintCmdInteger(4), pxPrintCmdInteger(5), pxPrintCmdInteger(6),
        },
    6);

    pxLoggerDebug(&logger, pxs8("No args\n"));

    pxLoggerTraceFmt(&logger, pxs8("strings = [${0}]8, [${1}]16, [${2}]32\n"),
        (PxPrintCmd[]) {
            pxPrintCmdString8(pxString8Vargs('h', 'e', 'l', 'l', 'o')),
            pxPrintCmdString16(pxString16Vargs('h', 'e', 'l', 'l', 'o')),
            pxPrintCmdString32(pxString32Vargs('h', 'e', 'l', 'l', 'o')),
        }, 3);

    pxLoggerSetLevel(&logger, PX_REPORT_LEVEL_TRACE);

    pxLoggerPrint(&logger, pxs8("\nLevel is \"TRACE\"\n\n"));

    pxLoggerFatal(&logger, pxs8("No args\n"));
    pxLoggerError(&logger, pxs8("No args\n"));
    pxLoggerWarn(&logger,  pxs8("No args\n"));

    pxLoggerInfoFmt(&logger, pxs8("With args [${0}, ${1}, ${2}, ${3}, ${4}, ${5}]\n"),
        (PxPrintCmd[]) {
            pxPrintCmdInteger(1), pxPrintCmdInteger(2), pxPrintCmdInteger(3),
            pxPrintCmdInteger(4), pxPrintCmdInteger(5), pxPrintCmdInteger(6),
        },
    6);

    pxLoggerDebug(&logger, pxs8("No args\n"));

    pxLoggerTraceFmt(&logger, pxs8("strings = [${0}]8, [${1}]16, [${2}]32\n"),
        (PxPrintCmd[]) {
            pxPrintCmdString8(pxString8Vargs('h', 'e', 'l', 'l', 'o')),
            pxPrintCmdString16(pxString16Vargs('h', 'e', 'l', 'l', 'o')),
            pxPrintCmdString32(pxString32Vargs('h', 'e', 'l', 'l', 'o')),
        }, 3);
}
