#define _POSIX_SOURCE

#include <utils/common.h>
#include <time.h>

void
getUtcTime(struct tm *result, time_t val)
{
    gmtime_r(&val, result);
}

