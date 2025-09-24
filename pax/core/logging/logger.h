#ifndef PX_CORE_LOGGING_LOGGER_H
#define PX_CORE_LOGGING_LOGGER_H

#include "import.h"

#define pxLoggerPrint(self, string) \
    pxLoggerPrintFmt(self, string, 0, 0)

#define pxLoggerFatal(self, string) \
    pxLoggerFatalFmt(self, string, 0, 0)

#define pxLoggerError(self, string) \
    pxLoggerErrorFmt(self, string, 0, 0)

#define pxLoggerWarn(self, string) \
    pxLoggerWarnFmt(self, string, 0, 0)

#define pxLoggerInfo(self, string) \
    pxLoggerInfoFmt(self, string, 0, 0)

#define pxLoggerDebug(self, string) \
    pxLoggerDebugFmt(self, string, 0, 0)

#define pxLoggerTrace(self, string) \
    pxLoggerTraceFmt(self, string, 0, 0)

typedef enum PxReportLevel
{
    PX_REPORT_LEVEL_NONE,

    PX_REPORT_LEVEL_PRINT,

    PX_REPORT_LEVEL_FATAL,
    PX_REPORT_LEVEL_ERROR,
    PX_REPORT_LEVEL_WARN,
    PX_REPORT_LEVEL_INFO,
    PX_REPORT_LEVEL_DEBUG,
    PX_REPORT_LEVEL_TRACE,
}
PxReportLevel;

typedef enum PxReportFlag
{
    PX_REPORT_FLAG_NONE  = 0,
    PX_REPORT_FLAG_LEVEL = 1 << 0,
    PX_REPORT_FLAG_COLOR = 1 << 1,
}
PxReportFlag;

typedef struct PxLogger
{
    PxReportLevel level;
    PxReportFlag  flags;

    PxTarget target;
}
PxLogger;

PxLogger
pxLoggerMake(PxTarget target, PxReportLevel level, PxReportFlag flags);

PxReportLevel
pxLoggerSetLevel(PxLogger* self, PxReportLevel level);

PxReportFlag
pxLoggerSetFlags(PxLogger* self, PxReportFlag flags);

pxb8
pxLoggerWriteStart(PxLogger* self, PxReportLevel level);

pxb8
pxLoggerWriteStop(PxLogger* self, PxReportLevel level);

pxb8
pxLoggerWriteFormat(PxLogger* self, PxString8 format, PxFormatMsg* values, pxiword length, PxReportLevel level);

/* Logging levels */

pxb8
pxLoggerPrintFmt(PxLogger* self, PxString8 format, PxFormatMsg* values, pxiword length);

pxb8
pxLoggerFatalFmt(PxLogger* self, PxString8 format, PxFormatMsg* values, pxiword length);

pxb8
pxLoggerErrorFmt(PxLogger* self, PxString8 format, PxFormatMsg* values, pxiword length);

pxb8
pxLoggerWarnFmt(PxLogger* self, PxString8 format, PxFormatMsg* values, pxiword length);

pxb8
pxLoggerInfoFmt(PxLogger* self, PxString8 format, PxFormatMsg* values, pxiword length);

pxb8
pxLoggerDebugFmt(PxLogger* self, PxString8 format, PxFormatMsg* values, pxiword length);

pxb8
pxLoggerTraceFmt(PxLogger* self, PxString8 format, PxFormatMsg* values, pxiword length);

#endif // PX_CORE_LOGGING_LOGGER_H
