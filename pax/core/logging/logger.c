#ifndef PX_CORE_LOGGING_LOGGER_C
#define PX_CORE_LOGGING_LOGGER_C

#include "logger.h"

PxLogger
pxLoggerReserve(PxArena* arena, pxiword length, PxWriter* writer)
{
    return (PxLogger) {
        .builder = pxBuilderReserve(arena, length),
        .writer  = writer,
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
pxLoggerStart(PxLogger* self, PxReportLevel level)
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
        [PX_REPORT_LEVEL_FATAL] = pxs8("FATAL | "),
        [PX_REPORT_LEVEL_ERROR] = pxs8("ERROR | "),
        [PX_REPORT_LEVEL_WARN]  = pxs8(" WARN | "),
        [PX_REPORT_LEVEL_INFO]  = pxs8(" INFO | "),
        [PX_REPORT_LEVEL_DEBUG] = pxs8("DEBUG | "),
        [PX_REPORT_LEVEL_TRACE] = pxs8("TRACE | "),
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
pxLoggerStop(PxLogger* self, PxReportLevel level)
{
    return pxWriterFlush(self->writer);
}

pxb8
pxLoggerFormat(PxLogger* self, PxReportLevel level, PxString8 format, pxiword start, pxiword stop, PxFormatCmd* list)
{
    if (self == 0 || level == PX_REPORT_LEVEL_NONE)
        return 0;

    if (level <= self->level) {
        pxBuilderClear(&self->builder);
        pxBuilderFormat(&self->builder, format, start, stop, list);

        pxLoggerStart(self, level);

        pxiword size = pxWriterMemory(self->writer,
            self->builder.memory, self->builder.size, 1);

        pxLoggerStop(self, level);
        pxBuilderClear(&self->builder);

        if (size != 0) return 1;
    }

    return 0;
}

#endif // PX_CORE_LOGGING_LOGGER_C
