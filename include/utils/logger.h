#ifndef UTILS_LOGGER_H
#define UTILS_LOGGER_H

#include "stringfunc.h"

typedef const char *Logger;

typedef enum LogLevel
{
    LogLevel_FATAL = 0,
    LogLevel_ERROR,
    LogLevel_WARN,
    LogLevel_INFO,
    LogLevel_DEBUG,
    LogLevel_TRACE
} LogLevel;

typedef void (*LogAppender)(LogLevel level,
	const char *logger, const char *message);

const LogAppender NullLogAppender;
const LogAppender StderrLogAppender;

void Logger_SetAppender(LogAppender appender);

void Logger_Log(Logger self, LogLevel level, const char *message);
void Logger_LogCB(Logger self, LogLevel level, StringFunc *callback);

#define LOGGER(name) name

#define LOG_FATAL(logger, what) Logger_Log(logger, LogLevel_FATAL, what)
#define LOGCB_FATAL(logger, what) Logger_LogCB(logger, LogLevel_FATAL, what)
#define LOG_ERROR(logger, what) Logger_Log(logger, LogLevel_ERROR, what)
#define LOGCB_ERROR(logger, what) Logger_LogCB(logger, LogLevel_ERROR, what)
#define LOG_WARN(logger, what) Logger_Log(logger, LogLevel_WARN, what)
#define LOGCB_WARN(logger, what) Logger_LogCB(logger, LogLevel_WARN, what)
#define LOG_INFO(logger, what) Logger_Log(logger, LogLevel_INFO, what)
#define LOGCB_INFO(logger, what) Logger_LogCB(logger, LogLevel_INFO, what)
#define LOG_DEBUG(logger, what) Logger_Log(logger, LogLevel_DEBUG, what)
#define LOGCB_DEBUG(logger, what) Logger_LogCB(logger, LogLevel_DEBUG, what)
#define LOG_TRACE(logger, what) Logger_Log(logger, LogLevel_TRACE, what)
#define LOGCB_TRACE(logger, what) Logger_LogCB(logger, LogLevel_TRACE, what)

#endif
