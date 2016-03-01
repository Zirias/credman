#include "stringbuilder.h"
#include "common.h"
#include "int.h"

#include <string.h>

struct StringBuilder
{
    size_t capacity;
    size_t length;
    char *buffer;
};

StringBuilder *
StringBuilder_Create(void)
{
    StringBuilder *self = xmalloc(sizeof(StringBuilder));
    self->capacity = 0;
    self->length = 0;
    self->buffer = 0;
    return self;
}

void
StringBuilder_Destroy(StringBuilder *self)
{
    if (!self) return;
    free(self->buffer);
    free(self);
    return;
}

void
StringBuilder_AppendString(StringBuilder *self, const char *append)
{
    size_t appendLen = strlen(append);
    if (self->length + appendLen > self->capacity)
    {
	self->capacity *= 2;
	if (self->length + appendLen > self->capacity)
	{
	    self->capacity = self->length + appendLen;
	}
	self->buffer = xrealloc(self->buffer, self->capacity + 1);
    }
    strcpy(self->buffer + self->length, append);
    self->length += appendLen;
    self->buffer[self->length] = 0;
}

void
StringBuilder_AppendInt(StringBuilder *self, int append)
{
    char *appendStr = int_ToString(append);
    StringBuilder_AppendString(self, appendStr);
    free(appendStr);
}

const char *
StringBuilder_AsString(const StringBuilder *self)
{
    return self->buffer;
}

