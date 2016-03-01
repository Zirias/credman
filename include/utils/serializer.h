#ifndef UTILS_SERIALIZER_H
#define UTILS_SERIALIZER_H

#include <utils/stringbuilder.h>
#include <time.h>

typedef struct ISerializer ISerializer;

struct ISerializer
{
    char *(*FormatInt)(ISerializer *self, int val);
    char *(*FormatFloat)(ISerializer *self, double val);
    char *(*FormatDateTime)(ISerializer *self, time_t val);

    void (*WriteValue)(ISerializer *self, const char *val);

    void (*StartProperty)(ISerializer *self, const char *name);
    void (*EndProperty)(ISerializer *self);

    void (*StartList)(ISerializer *self, const char *name);
    void (*EndList)(ISerializer *self);

    void (*StartObject)(ISerializer *self, const char *name);
    void (*EndObject)(ISerializer *self);

    char *(*CreateResult)(ISerializer *self);

    void (*Destroy)(ISerializer *self);

    ISerializer *base;
};

typedef ISerializer *(*SerializerFactory)(void);

void Serializer_DeriveInterface(ISerializer *from, ISerializer *to);

typedef struct BaseSerializer BaseSerializer;

BaseSerializer *BaseSerializer_Create(void);
StringBuilder *BaseSerializer_Builder(BaseSerializer *self);

#endif
