#ifndef PX_CORE_LOGGING_LOGGER_C
#define PX_CORE_LOGGING_LOGGER_C

#include "logger.h"

PxLogger
pxLoggerReserve(PxArena* arena, pxiword length, PxWriter writer, PxReportLevel level, PxReportFlag flags)
{
    return (PxLogger) {
        .builder = pxBuilderReserve(arena, length),
        .writer  = writer,
        .level   = level,
        .flags   = flags,
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

void
pxLoggerFlush(PxLogger* self)
{
    pxWriterFlush(&self->writer);
}

    /*
    switch (level) {
        case PX_REPORT_LEVEL_FATAL:
            if ((self->flags & PX_REPORT_FLAG_COLORS) != 0)
                pxWriterString8(&self->writer, pxs8("\x1b[35m"));

            pxWriterString8(&self->writer, pxs8("[FATAL] "));

            if ((self->flags & PX_REPORT_FLAG_COLORS) != 0)
                pxWriterString8(&self->writer, pxs8("\x1b[0m"));
        break;

        case PX_REPORT_LEVEL_ERROR:
            if ((self->flags & PX_REPORT_FLAG_COLORS) != 0)
                pxWriterString8(&self->writer, pxs8("\x1b[31m"));

            pxWriterString8(&self->writer, pxs8("[ERROR] "));

            if ((self->flags & PX_REPORT_FLAG_COLORS) != 0)
                pxWriterString8(&self->writer, pxs8("\x1b[0m"));
        break;

        case PX_REPORT_LEVEL_WARN:
            if ((self->flags & PX_REPORT_FLAG_COLORS) != 0)
                pxWriterString8(&self->writer, pxs8("\x1b[33m"));

            pxWriterString8(&self->writer, pxs8("[WARN] "));

            if ((self->flags & PX_REPORT_FLAG_COLORS) != 0)
                pxWriterString8(&self->writer, pxs8("\x1b[0m"));
        break;

        case PX_REPORT_LEVEL_MESSAGE:
            pxWriterString8(&self->writer, pxs8("[MESSAGE] "));
        break;

        case PX_REPORT_LEVEL_INFO:
            if ((self->flags & PX_REPORT_FLAG_COLORS) != 0)
                pxWriterString8(&self->writer, pxs8("\x1b[32m"));

            pxWriterString8(&self->writer, pxs8("[INFO] "));

            if ((self->flags & PX_REPORT_FLAG_COLORS) != 0)
                pxWriterString8(&self->writer, pxs8("\x1b[0m"));
        break;

        case PX_REPORT_LEVEL_DEBUG:
            if ((self->flags & PX_REPORT_FLAG_COLORS) != 0)
                pxWriterString8(&self->writer, pxs8("\x1b[36m"));

            pxWriterString8(&self->writer, pxs8("[DEBUG] "));

            if ((self->flags & PX_REPORT_FLAG_COLORS) != 0)
                pxWriterString8(&self->writer, pxs8("\x1b[0m"));
        break;

        case PX_REPORT_LEVEL_TRACE:
            if ((self->flags & PX_REPORT_FLAG_COLORS) != 0)
                pxWriterString8(&self->writer, pxs8("\x1b[34m"));

            pxWriterString8(&self->writer, pxs8("[TRACE] "));

            if ((self->flags & PX_REPORT_FLAG_COLORS) != 0)
                pxWriterString8(&self->writer, pxs8("\x1b[0m"));
        break;

        default: break;
    }
    */

pxb8
pxLoggerFormat(PxLogger* self, PxReportLevel level, PxString8 format, pxiword length, PxBuilderCmd* list)
{
    pxBuilderClear(&self->builder);

    if (level <= self->level || level == PX_REPORT_LEVEL_NONE) {
        pxBuilderFormat(&self->builder, format, 0, length, list);

        PxString32 string = {
            .memory = self->builder.memory,
            .length = self->builder.size,
        };

        pxiword size = pxWriterString32(&self->writer, string);

        if (size != 0) return 1;
    }

    return 0;
}

#endif // PX_CORE_LOGGING_LOGGER_C
