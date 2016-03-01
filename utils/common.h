#ifndef UTILS_COMMON_H
#define UTILS_COMMON_H

#include <stdlib.h>

void *xmalloc(size_t size);
void *xrealloc(void *alloc, size_t newsize);

char *copyString(const char *orig);

#endif
