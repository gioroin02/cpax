#ifndef PX_CORE_LOGGING_LOGGER_C
#define PX_CORE_LOGGING_LOGGER_C

#include "logger.h"

PxLogger
pxLoggerReserve(PxArena* arena, pxiword length, PxReportLevel level, PxReportFlag flags, PxWriter* writer)
{
    return (PxLogger) {
        .builder = pxBuilderReserve(arena, length),
        .level   = level,
        .flags   = flags,
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

void
pxLoggerFlush(PxLogger* self)
{
    pxWriterFlush(self->writer);
}

    /*
    switch (level) {
        case PX_REPORT_LEVEL_FATAL:
            if ((self->flags & PX_REPORT_FLAG_COLORS) != 0)
                pxWriterString8(self->writer, pxs8("\x1b[35m"));

            pxWriterString8(self->writer, pxs8("[FATAL] "));

            if ((self->flags & PX_REPORT_FLAG_COLORS) != 0)
                pxWriterString8(self->writer, pxs8("\x1b[0m"));
        break;

        case PX_REPORT_LEVEL_ERROR:
            if ((self->flags & PX_REPORT_FLAG_COLORS) != 0)
                pxWriterString8(self->writer, pxs8("\x1b[31m"));

            pxWriterString8(self->writer, pxs8("[ERROR] "));

            if ((self->flags & PX_REPORT_FLAG_COLORS) != 0)
                pxWriterString8(self->writer, pxs8("\x1b[0m"));
        break;

        case PX_REPORT_LEVEL_WARN:
            if ((self->flags & PX_REPORT_FLAG_COLORS) != 0)
                pxWriterString8(self->writer, pxs8("\x1b[33m"));

            pxWriterString8(self->writer, pxs8("[WARN] "));

            if ((self->flags & PX_REPORT_FLAG_COLORS) != 0)
                pxWriterString8(self->writer, pxs8("\x1b[0m"));
        break;

        case PX_REPORT_LEVEL_MESSAGE:
            pxWriterString8(self->writer, pxs8("[MESSAGE] "));
        break;

        case PX_REPORT_LEVEL_INFO:
            if ((self->flags & PX_REPORT_FLAG_COLORS) != 0)
                pxWriterString8(self->writer, pxs8("\x1b[32m"));

            pxWriterString8(self->writer, pxs8("[INFO] "));

            if ((self->flags & PX_REPORT_FLAG_COLORS) != 0)
                pxWriterString8(self->writer, pxs8("\x1b[0m"));
        break;

        case PX_REPORT_LEVEL_DEBUG:
            if ((self->flags & PX_REPORT_FLAG_COLORS) != 0)
                pxWriterString8(self->writer, pxs8("\x1b[36m"));

            pxWriterString8(self->writer, pxs8("[DEBUG] "));

            if ((self->flags & PX_REPORT_FLAG_COLORS) != 0)
                pxWriterString8(self->writer, pxs8("\x1b[0m"));
        break;

        case PX_REPORT_LEVEL_TRACE:
            if ((self->flags & PX_REPORT_FLAG_COLORS) != 0)
                pxWriterString8(self->writer, pxs8("\x1b[34m"));

            pxWriterString8(self->writer, pxs8("[TRACE] "));

            if ((self->flags & PX_REPORT_FLAG_COLORS) != 0)
                pxWriterString8(self->writer, pxs8("\x1b[0m"));
        break;

        default: break;
    }
    */

void
pxLoggerHead(PxLogger* self, PxReportLevel level)
{
    if ((self->flags & PX_REPORT_FLAG_LEVEL) == 0) return;

    if ((self->flags & PX_REPORT_FLAG_COLOR) != 0) {
        switch (level) {
            case PX_REPORT_LEVEL_FATAL:
                pxWriterString8(self->writer, pxs8("\x1b[35m"));
            break;

            case PX_REPORT_LEVEL_ERROR:
                pxWriterString8(self->writer, pxs8("\x1b[31m"));
            break;

            case PX_REPORT_LEVEL_WARN:
                pxWriterString8(self->writer, pxs8("\x1b[33m"));
            break;

            case PX_REPORT_LEVEL_INFO:
                pxWriterString8(self->writer, pxs8("\x1b[32m"));
            break;

            case PX_REPORT_LEVEL_DEBUG:
                pxWriterString8(self->writer, pxs8("\x1b[36m"));
            break;

            case PX_REPORT_LEVEL_TRACE:
                pxWriterString8(self->writer, pxs8("\x1b[34m"));
            break;

            default: break;
        }
    }

    switch (level) {
        case PX_REPORT_LEVEL_FATAL:
            pxWriterString8(self->writer, pxs8("FATAL "));
        break;

        case PX_REPORT_LEVEL_ERROR:
            pxWriterString8(self->writer, pxs8("ERROR "));
        break;

        case PX_REPORT_LEVEL_WARN:
            pxWriterString8(self->writer, pxs8("WARN "));
        break;

        case PX_REPORT_LEVEL_MESSAGE:
            pxWriterString8(self->writer, pxs8("MESSG "));
        break;

        case PX_REPORT_LEVEL_INFO:
            pxWriterString8(self->writer, pxs8("INFO "));
        break;

        case PX_REPORT_LEVEL_DEBUG:
            pxWriterString8(self->writer, pxs8("DEBUG "));
        break;

        case PX_REPORT_LEVEL_TRACE:
            pxWriterString8(self->writer, pxs8("TRACE "));
        break;


        default: break;
    }

    if ((self->flags & PX_REPORT_FLAG_COLOR) != 0) {
        switch (level) {
            case PX_REPORT_LEVEL_FATAL:
            case PX_REPORT_LEVEL_ERROR:
            case PX_REPORT_LEVEL_WARN:
            case PX_REPORT_LEVEL_INFO:
            case PX_REPORT_LEVEL_DEBUG:
            case PX_REPORT_LEVEL_TRACE:
                pxWriterString8(self->writer, pxs8("\x1b[0m"));
            break;

            default: break;
        }
    }
}

pxb8
pxLoggerFormat(PxLogger* self, PxReportLevel level, PxString8 format, pxiword start, pxiword stop, PxBuilderCmd* list)
{
    pxBuilderClear(&self->builder);

    if (level <= self->level |level == PX_REPORT_LEVEL_NONE) {
        pxBuilderFormat(&self->builder, format, start, stop, list);

        pxLoggerHead(self, level);

        PxString8 string = {
            .memory = self->builder.memory,
            .length = self->builder.size,
        };

        pxiword size = pxWriterString8(self->writer, string);

        pxWriterFlush(self->writer);

        if (size != 0) return 1;
    }

    return 0;
}

#endif // PX_CORE_LOGGING_LOGGER_C
