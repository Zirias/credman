#include <model/cred.h>
#include <utils/common.h>

struct Cred
{
    char *username;
    char *password;
    char *description;
    time_t created;
    time_t changed;
};

Cred *
Cred_Create(void)
{
    Cred *self = xmalloc(sizeof(Cred));
    self->username = 0;
    self->password = 0;
    self->description = 0;
    time(&(self->created));
    self->changed = 0;
    return self;
}

Cred *
Cred_Copy(const Cred *rhs)
{
    Cred *self = xmalloc(sizeof(Cred));
    self->username = copyString(rhs->username);
    self->password = copyString(rhs->password);
    self->description = copyString(rhs->description);
    self->created = rhs->created;
    self->changed = rhs->changed;
    return self;
}

void
Cred_Destroy(Cred *self)
{
    if (!self) return;
    free(self->username);
    free(self->password);
    free(self->description);
    free(self);
}

const char *
Cred_Username(const Cred *self)
{
    return self->username;
}

const char *
Cred_Password(const Cred *self)
{
    return self->password;
}


const char *
Cred_Description(const Cred *self)
{
    return self->description;
}

time_t
Cred_Created(const Cred *self)
{
    return self->created;
}

time_t
Cred_Changed(const Cred *self)
{
    return self->changed;
}

void
Cred_SetUsername(Cred *self, const char *username)
{
    free(self->username);
    self->username = copyString(username);
    time(&(self->changed));
}

void
Cred_SetPassword(Cred *self, const char *password)
{
    free(self->password);
    self->password = copyString(password);
    time(&(self->changed));
}

void
Cred_SetDescription(Cred *self, const char *description)
{
    free(self->description);
    self->description = copyString(description);
}

char *
Cred_Serialize(const Cred *self, SerializerFactory serializerFactory)
{
    ISerializer *serializer = serializerFactory();
    char *val;

    serializer->StartObject(serializer, 0);

    serializer->StartProperty(serializer, "Username");
    serializer->WriteValue(serializer, self->username);
    serializer->EndProperty(serializer);

    serializer->StartProperty(serializer, "Password");
    serializer->WriteValue(serializer, self->password);
    serializer->EndProperty(serializer);

    serializer->StartProperty(serializer, "Created");
    val = serializer->FormatDateTime(serializer, self->created);
    serializer->WriteValue(serializer, val);
    free(val);
    serializer->EndProperty(serializer);

    serializer->StartProperty(serializer, "Changed");
    val = serializer->FormatDateTime(serializer, self->changed);
    serializer->WriteValue(serializer, val);
    free(val);
    serializer->EndProperty(serializer);

    serializer->EndObject(serializer);

    return serializer->CreateResult(serializer);
}

