#include <utils/logger.h>
#include <utils/common.h>
#include <utils/stringbuilder.h>

#include <stdio.h>

struct Logger
{
    const char *name;
};

static void
_nullLogAppender(LogLevel level, const char *logger, const char *message)
{
    (void)level;
    (void)logger;
    (void)message;
}

static const char * const _logLevelTag[] =
{
    "[FAT]",
    "[ERR]",
    "[WRN]",
    "[INF]",
    "[DBG]",
    "[TRC]"
};

static void
_stderrLogAppender(LogLevel level, const char *logger, const char *message)
{
    StringBuilder *builder = StringBuilder_Create();
    StringBuilder_AppendString(builder, _logLevelTag[level]);
    StringBuilder_AppendString(builder, " {");
    StringBuilder_AppendString(builder, logger);
    StringBuilder_AppendString(builder, "} ");
    StringBuilder_AppendString(builder, message);
    StringBuilder_AppendString(builder, "\n");
    fputs(StringBuilder_AsString(builder), stderr);
    StringBuilder_Destroy(builder);
}

const LogAppender NullLogAppender = _nullLogAppender;
const LogAppender StderrLogAppender = _stderrLogAppender;

static LogAppender _appender = _nullLogAppender;

void
Logger_SetAppender(LogAppender appender)
{
    if (appender) _appender = appender;
}

void
Logger_Log(Logger self, LogLevel level, const char *message)
{
    _appender(level, self, message);
}

void
Logger_LogCB(Logger self, LogLevel level, StringFunc *callback)
{
    _appender(level, self, callback->Invoke(callback));
    if (callback->Destroy) callback->Destroy(callback);
}

