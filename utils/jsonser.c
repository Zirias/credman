#include <utils/jsonser.h>
#include <utils/serializer.h>
#include <utils/common.h>
#include <utils/logger.h>
#include <string.h>

static Logger logger = LOGGER("Utils.JsonSerializer");

typedef enum StateFlags
{
    StateFlags_Normal = 0,
    StateFlags_InList = 1<<0,
    StateFlags_InObject = 1<<1,
    StateFlags_InProperty = 1<<2,
    StateFlags_AtStart = 1<<3
} StateFlags;

typedef struct JsonState
{
    StateFlags flags;
    const char *name;
} JsonState;

struct JsonSerializer
{
    ISerializer impl;
    JsonOptions options;
    JsonState state[64];
    JsonState *sp;
    int indent;
};

static char *
quote(const char *val)
{
    char *quoted = xmalloc(strlen(val)*2 + 2);
    char *w = quoted;
    *w++ = '"';
    while (*val)
    {
	if ((*val == '"') || (*val == '\\')) *w++ = '\\';
	*w++ = *val++;
    }
    *w++ = '"';
    *w = 0;
    return quoted;
}

static void
indent(JsonSerializer *self, StringBuilder *builder)
{
    if (self->options.formatting == JsonFormatting_Indented)
    {
	StringBuilder_AppendString(builder, "\n");
	for (int i = 0; i < self->indent; ++i)
	{
	    StringBuilder_AppendString(builder, "  ");
	}
    }
}

static void
startValue(JsonSerializer *self, StringBuilder *builder)
{
    if (!self->sp->flags) return;
    if (!(self->sp->flags & (StateFlags_InList|StateFlags_InProperty)))
    {
	LOG_ERROR(logger, "Trying to write value in invalid state.");
	return;
    }

    if (!(self->sp->flags & StateFlags_AtStart))
    {
	if (self->sp->flags & StateFlags_InProperty)
	{
	    LOG_ERROR(logger, "Trying to write multiple values for property.");
	    return;
	}
	StringBuilder_AppendString(builder, ",");
    }
    if (self->sp->flags & StateFlags_InList)
    {
	indent(self, builder);
    }
}

static char *
FormatInt(ISerializer *self, int val)
{
    return self->base->FormatInt(self->base, val);
}

static char *
FormatFloat(ISerializer *self, double val)
{
    return self->base->FormatFloat(self->base, val);
}

static char *
FormatDateTime(ISerializer *self, time_t val)
{
    return self->base->FormatDateTime(self->base, val);
}

static void
WriteValue(ISerializer *self, const char *val)
{
    JsonSerializer *myself = (JsonSerializer *)self;
    BaseSerializer *mybase = (BaseSerializer *)self->base;
    StringBuilder *builder = BaseSerializer_Builder(mybase);
    
    startValue(myself, builder);

    char *quoted = quote(val);
    StringBuilder_AppendString(builder, quoted);
    free(quoted);

    myself->sp->flags &= ~StateFlags_AtStart;
}

static void
StartProperty(ISerializer *self, const char *name)
{
    JsonSerializer *myself = (JsonSerializer *)self;
    BaseSerializer *mybase = (BaseSerializer *)self->base;
    StringBuilder *builder = BaseSerializer_Builder(mybase);

    if (!(myself->sp->flags & StateFlags_InObject))
    {
	LOG_ERROR(logger, "Trying to start property outside of object.");
	return;
    }

    if (!(myself->sp->flags & StateFlags_AtStart))
    {
	StringBuilder_AppendString(builder, ",");
    }
    indent(myself, builder);

    char *quoted = quote(name);
    StringBuilder_AppendString(builder, quoted);
    free(quoted);
    if (myself->options.formatting == JsonFormatting_Indented)
    {
	StringBuilder_AppendString(builder, " : ");
    }
    else
    {
	StringBuilder_AppendString(builder, ":");
    }
    --myself->sp;
    myself->sp->flags = StateFlags_InProperty | StateFlags_AtStart;
    myself->sp->name = name;
}

static void
EndProperty(ISerializer *self)
{
    JsonSerializer *myself = (JsonSerializer *)self;
    BaseSerializer *mybase = (BaseSerializer *)self->base;
    StringBuilder *builder = BaseSerializer_Builder(mybase);

    if (!(myself->sp->flags & StateFlags_InProperty))
    {
	LOG_ERROR(logger, "Trying to end property while not in property.");
	return;
    }

    if (myself->sp->flags & StateFlags_AtStart)
    {
	StringBuilder_AppendString(builder, "null");
    }

    ++myself->sp;
    myself->sp->flags &= ~StateFlags_AtStart;
}

static void
StartList(ISerializer *self, const char *name)
{
    JsonSerializer *myself = (JsonSerializer *)self;
    BaseSerializer *mybase = (BaseSerializer *)self->base;
    StringBuilder *builder = BaseSerializer_Builder(mybase);

    startValue(myself, builder);

    StringBuilder_AppendString(builder, "[");
    --myself->sp;
    myself->sp->flags = StateFlags_InList | StateFlags_AtStart;
    myself->sp->name = name;
    ++myself->indent;
}

static void
EndList(ISerializer *self)
{
    JsonSerializer *myself = (JsonSerializer *)self;
    BaseSerializer *mybase = (BaseSerializer *)self->base;
    StringBuilder *builder = BaseSerializer_Builder(mybase);

    if (!(myself->sp->flags & StateFlags_InList))
    {
	LOG_ERROR(logger, "Trying to end list while not in list.");
	return;
    }

    StateFlags flags = myself->sp->flags;
    ++myself->sp;
    --myself->indent;
    if (!(flags & StateFlags_AtStart))
    {
	indent(myself, builder);
    }
    StringBuilder_AppendString(builder, "]");
    myself->sp->flags &= ~StateFlags_AtStart;
}

static void
StartObject(ISerializer *self, const char *name)
{
    JsonSerializer *myself = (JsonSerializer *)self;
    BaseSerializer *mybase = (BaseSerializer *)self->base;
    StringBuilder *builder = BaseSerializer_Builder(mybase);

    startValue(myself, builder);

    StringBuilder_AppendString(builder, "{");
    --myself->sp;
    myself->sp->flags = StateFlags_InObject | StateFlags_AtStart;
    myself->sp->name = name;
    ++myself->indent;
}

static void
EndObject(ISerializer *self)
{
    JsonSerializer *myself = (JsonSerializer *)self;
    BaseSerializer *mybase = (BaseSerializer *)self->base;
    StringBuilder *builder = BaseSerializer_Builder(mybase);

    if (!(myself->sp->flags & StateFlags_InObject))
    {
	LOG_ERROR(logger, "Trying to end object while not in object.");
	return;
    }

    StateFlags flags = myself->sp->flags;
    ++myself->sp;
    --myself->indent;
    if (!(flags & StateFlags_AtStart))
    {
	indent(myself, builder);
    }
    StringBuilder_AppendString(builder, "}");
    myself->sp->flags &= ~StateFlags_AtStart;
}

static char *
CreateResult(ISerializer *self)
{
    return self->base->CreateResult(self->base);
}

static void
Destroy(ISerializer *self)
{
    if (!self) return;
    self->base->Destroy(self->base);
    free(self);
}

JsonSerializer *
JsonSerializer_Create(JsonOptions options)
{
    BaseSerializer *base = BaseSerializer_Create();
    JsonSerializer *self = xmalloc(sizeof(JsonSerializer));
    memset(self, 0, sizeof(JsonSerializer));

    self->impl.base = (ISerializer *)base;

    self->impl.FormatInt = FormatInt;
    self->impl.FormatFloat = FormatFloat;
    self->impl.FormatDateTime = FormatDateTime;
    self->impl.WriteValue = WriteValue;
    self->impl.StartProperty = StartProperty;
    self->impl.EndProperty = EndProperty;
    self->impl.StartList = StartList;
    self->impl.EndList = EndList;
    self->impl.StartObject = StartObject;
    self->impl.EndObject = EndObject;
    self->impl.CreateResult = CreateResult;
    self->impl.Destroy = Destroy;

    self->options = options;
    self->sp = &(self->state[63]);

    return self;
}

