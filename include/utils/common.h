#ifndef UTILS_COMMON_H
#define UTILS_COMMON_H

#include <stdlib.h>
#include <time.h>

void *xmalloc(size_t size);
void *xrealloc(void *alloc, size_t newsize);

char *copyString(const char *orig);

void getUtcTime(struct tm *result, time_t val);

#endif
