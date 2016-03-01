#include <utils/common.h>
#include <utils/logger.h>
#include <utils/stringbuilder.h>

#include <string.h>

static Logger _log = LOGGER("Utils.Common");

void *
xmalloc(size_t size)
{
    void *alloc = malloc(size);
    if (!alloc)
    {
	LOG_FATAL(_log, "xmalloc(): Failed to allocate memory.");
	exit(EXIT_FAILURE);
    }
    return alloc;
}

void *
xrealloc(void *ptr, size_t size)
{
    void *alloc = realloc(ptr, size);
    if (!alloc)
    {
	LOG_FATAL(_log, "xrealloc(): Failed to allocate memory.");
	exit(EXIT_FAILURE);
    }
    return alloc;
}

char *
copyString(const char *orig)
{
    if (!orig) return 0;
    char *copy = xmalloc(strlen(orig) + 1);
    strcpy(copy, orig);
    return copy;
}

