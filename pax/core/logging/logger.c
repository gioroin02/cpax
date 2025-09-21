#ifndef PX_CORE_LOGGING_LOGGER_C
#define PX_CORE_LOGGING_LOGGER_C

#include "logger.h"

PxLogger
pxLoggerMake(PxWriter* writer, PxReportLevel level, PxReportFlag flags)
{
    return (PxLogger) {
        .level  = level,
        .flags  = flags,
        .writer = writer,
    };
}

PxReportLevel
pxLoggerSetLevel(PxLogger* self, PxReportLevel level)
{
    PxReportLevel result =
        self->level;

    self->level = level;

    return result;
}

PxReportFlag
pxLoggerSetFlags(PxLogger* self, PxReportFlag flags)
{
    PxReportFlag result =
        self->flags;

    self->flags = flags;

    return result;
}

pxb8
pxLoggerWriteStart(PxLogger* self, PxReportLevel level)
{
    PxString8 reset = pxs8("\x1b[0m");

    PxString8 colors[] = {
        [PX_REPORT_LEVEL_FATAL] = pxs8("\x1b[35m"),
        [PX_REPORT_LEVEL_ERROR] = pxs8("\x1b[31m"),
        [PX_REPORT_LEVEL_WARN]  = pxs8("\x1b[33m"),
        [PX_REPORT_LEVEL_INFO]  = pxs8("\x1b[32m"),
        [PX_REPORT_LEVEL_DEBUG] = pxs8("\x1b[36m"),
        [PX_REPORT_LEVEL_TRACE] = pxs8("\x1b[34m"),
    };

    PxString8 headings[] = {
        [PX_REPORT_LEVEL_FATAL] = pxs8("[ FATAL ] "),
        [PX_REPORT_LEVEL_ERROR] = pxs8("[ ERROR ] "),
        [PX_REPORT_LEVEL_WARN]  = pxs8("[  WARN ] "),
        [PX_REPORT_LEVEL_INFO]  = pxs8("[  INFO ] "),
        [PX_REPORT_LEVEL_DEBUG] = pxs8("[ DEBUG ] "),
        [PX_REPORT_LEVEL_TRACE] = pxs8("[ TRACE ] "),
    };

    pxiword result = 0;

    if ((self->flags & PX_REPORT_FLAG_LEVEL) != 0) {
        if ((self->flags & PX_REPORT_FLAG_COLOR) != 0)
            result += pxWriterString8(self->writer, colors[level]);

        result += pxWriterString8(self->writer, headings[level]);

        if ((self->flags & PX_REPORT_FLAG_COLOR) != 0)
            result += pxWriterString8(self->writer, reset);
    }

    return result;
}

pxb8
pxLoggerWriteStop(PxLogger* self, PxReportLevel level)
{
    return pxWriterFlush(self->writer);
}

pxb8
pxLoggerWriteFmt(PxLogger* self, PxString8 format, PxPrintCmd* values, pxiword length, PxReportLevel level)
{
    if (level == PX_REPORT_LEVEL_NONE)
        return 0;

    if (self->level >= level) {
        pxLoggerWriteStart(self, level);
        pxWriterFmt(self->writer, format, values, length);
        pxLoggerWriteStop(self, level);

        return 1;
    }

    return 0;
}

pxb8
pxLoggerPrintFmt(PxLogger* self, PxString8 format, PxPrintCmd* values, pxiword length)
{
    return pxLoggerWriteFmt(self, format, values, length, PX_REPORT_LEVEL_PRINT);
}

pxb8
pxLoggerFatalFmt(PxLogger* self, PxString8 format, PxPrintCmd* values, pxiword length)
{
    return pxLoggerWriteFmt(self, format, values, length, PX_REPORT_LEVEL_FATAL);
}

pxb8
pxLoggerErrorFmt(PxLogger* self, PxString8 format, PxPrintCmd* values, pxiword length)
{
    return pxLoggerWriteFmt(self, format, values, length, PX_REPORT_LEVEL_ERROR);
}

pxb8
pxLoggerWarnFmt(PxLogger* self, PxString8 format, PxPrintCmd* values, pxiword length)
{
    return pxLoggerWriteFmt(self, format, values, length, PX_REPORT_LEVEL_WARN);
}

pxb8
pxLoggerInfoFmt(PxLogger* self, PxString8 format, PxPrintCmd* values, pxiword length)
{
    return pxLoggerWriteFmt(self, format, values, length, PX_REPORT_LEVEL_INFO);
}

pxb8
pxLoggerDebugFmt(PxLogger* self, PxString8 format, PxPrintCmd* values, pxiword length)
{
    return pxLoggerWriteFmt(self, format, values, length, PX_REPORT_LEVEL_DEBUG);
}

pxb8
pxLoggerTraceFmt(PxLogger* self, PxString8 format, PxPrintCmd* values, pxiword length)
{
    return pxLoggerWriteFmt(self, format, values, length, PX_REPORT_LEVEL_TRACE);
}

#endif // PX_CORE_LOGGING_LOGGER_C
