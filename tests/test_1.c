#include <utils/logger.h>
#include <utils/stringbuilder.h>

static Logger _log = LOGGER("Tests.Test_1");

int
main(void)
{
    Logger_SetAppender(StderrLogAppender);

    StringBuilder *builder = StringBuilder_Create();
    StringBuilder_AppendString(builder, "Test ");
    StringBuilder_AppendInt(builder, 42);
    StringBuilder_AppendString(builder, " foo!!!");
   
    LOG_INFO(_log, StringBuilder_AsString(builder));
    StringBuilder_Destroy(builder);

    return 0;
}
