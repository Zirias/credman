#include <utils/serializer.h>
#include <utils/common.h>
#include <utils/int.h>
#include <stdio.h>
#include <string.h>

#define ISO_UTC "%Y-%m-%dT%H:%M:%SZ"

struct BaseSerializer
{
    ISerializer impl;
    StringBuilder *builder;
};

void
Serializer_DeriveInterface(ISerializer *from, ISerializer *to)
{
    memcpy(to, from, sizeof(ISerializer));
    to->base = from;
}

static char *
FormatInt(ISerializer *self, int val)
{
    (void)self;

    return int_ToString(val);
}

static char *
FormatFloat(ISerializer *self, double val)
{
    (void)self;

    char buf[24];
    snprintf(buf, 24, "%.20g", val);
    return copyString(buf);
}

static char *
FormatDateTime(ISerializer *self, time_t val)
{
    (void)self;

    char *result = xmalloc(21);
    struct tm stm;
    getUtcTime(&stm, val);
    strftime(result, 21, ISO_UTC, &stm);
    return result;
}

static void
Destroy(ISerializer *self)
{
    if (!self) return;
    BaseSerializer *myself = (BaseSerializer *)self;
    StringBuilder_Destroy(myself->builder);
    free(myself);
}

BaseSerializer *
BaseSerializer_Create(void)
{
    BaseSerializer *self = xmalloc(sizeof(BaseSerializer));
    self->impl.FormatInt = FormatInt;
    self->impl.FormatFloat = FormatFloat;
    self->impl.FormatDateTime = FormatDateTime;
    self->impl.Destroy = Destroy;
    self->builder = StringBuilder_Create();
    return self;
}

