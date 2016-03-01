#include <model/cred.h>
#include <utils/jsonser.h>
#include <utils/logger.h>
#include <stdlib.h>

static Logger logger = LOGGER("Tests.Test_2");

static ISerializer *
indentingSerializer(void)
{
    JsonSerializer *ser = JsonSerializer_Create((JsonOptions)
    {
	.formatting = JsonFormatting_Indented
    });
    return (ISerializer *)ser;
}

static ISerializer *
compactSerializer(void)
{
    JsonSerializer *ser = JsonSerializer_Create((JsonOptions){0});
    return (ISerializer *)ser;
}

static char *
serializeExample(SerializerFactory factory, Cred *cred)
{
    ISerializer *serializer = factory();
    serializer->StartObject(serializer, "test_2");

    serializer->StartProperty(serializer, "cred");
    Cred_SerializeTo(cred, serializer);
    serializer->EndProperty(serializer);

    serializer->StartProperty(serializer, "testlist");
    serializer->StartList(serializer, 0);
    serializer->WriteValue(serializer, "one");
    serializer->WriteValue(serializer, "two");
    serializer->WriteValue(serializer, "three");
    serializer->EndList(serializer);
    serializer->EndProperty(serializer);

    serializer->StartProperty(serializer, "emptylist");
    serializer->StartList(serializer, 0);
    serializer->EndList(serializer);
    serializer->EndProperty(serializer);
    
    serializer->StartProperty(serializer, "specialchars");
    serializer->WriteValue(serializer, "test\"quoted\"\\back");
    serializer->EndProperty(serializer);

    serializer->StartProperty(serializer, "emptyobject");
    serializer->StartObject(serializer, 0);
    serializer->EndObject(serializer);
    serializer->EndProperty(serializer);
    
    serializer->EndObject(serializer);

    char *result = serializer->CreateResult(serializer);
    serializer->Destroy(serializer);
    return result;
}

int
main(void)
{
    Logger_SetAppender(StderrLogAppender);

    Cred *cred = Cred_Create();
    Cred_SetUsername(cred, "bob");
    Cred_SetPassword(cred, "12345");

    char *serialized = serializeExample(indentingSerializer, cred);
    LOG_INFO(logger, serialized);
    free(serialized);

    serialized = serializeExample(compactSerializer, cred);
    LOG_INFO(logger, serialized);
    free(serialized);

    Cred_Destroy(cred);
}

