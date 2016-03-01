#ifndef UTILS_STRINGBUILDER_H
#define UTILS_STRINGBUILDER_H

typedef struct StringBuilder StringBuilder;

StringBuilder *StringBuilder_Create(void);
void StringBuilder_Destroy(StringBuilder *self);

void StringBuilder_AppendString(StringBuilder *self, const char *append);
void StringBuilder_AppendInt(StringBuilder *self, int append);
const char *StringBuilder_AsString(const StringBuilder *self);

#endif
